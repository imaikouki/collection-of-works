//=============================================================================
//
// NCMBへHTTPリクエスト処理 [PostNcmb.cpp]
// Author : Imai
//
//=============================================================================
#include <string>
#include <iostream>
#include <algorithm>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>
#include <cpprest/json.h>
#include <vector>
#include <codecvt>
#include <cstring>

using namespace utility;
using namespace web;
using namespace web::http;
using namespace web::http::client;

//=============================================================================
// UTF-8のバイト配列に変換
//=============================================================================
std::vector<char> ConvertUtilityStringToByteArray(const utility::string_t& str)
{
	std::string utf8Str = utility::conversions::to_utf8string(str);
	std::vector<char> byteArray(utf8Str.begin(), utf8Str.end());
	byteArray.push_back('\0'); // 文字列の終端を追加

	return byteArray;
}

//=============================================================================
// Base64に変換
//=============================================================================
utility::string_t GetHMACAsBase64(const utility::string_t& data, const utility::string_t& clientKey) 
{
	// データとクライアントキーをバイト配列に変換
	std::vector<char> contentBytes = ConvertUtilityStringToByteArray(data);
	std::vector<char> secretKeyBytes = ConvertUtilityStringToByteArray(clientKey);

	// バイト配列からポインタを取得
	const char* secretKey = secretKeyBytes.data();
	const char* content = contentBytes.data();

	// HMAC-SHA256ハッシュを計算
	unsigned char result[EVP_MAX_MD_SIZE];
	unsigned int resultLen;

	HMAC(EVP_sha256(), reinterpret_cast<const unsigned char*>(secretKey), clientKey.length(),
		reinterpret_cast<const unsigned char*>(content), data.length(), result, &resultLen);

	// 結果をBase64エンコードする
	std::string base64Result;
	BIO* bmem = BIO_new(BIO_s_mem());
	BIO* b64 = BIO_new(BIO_f_base64());
	BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL);
	BIO_push(b64, bmem);
	BIO_write(b64, result, resultLen);
	BIO_flush(b64);

	BUF_MEM* bptr;
	BIO_get_mem_ptr(b64, &bptr);

	base64Result.assign(bptr->data, bptr->data + bptr->length);
	BIO_free_all(b64);

	// Base64エンコード結果をutility::string_t型に変換して返す
	utility::string_t base64String = utility::conversions::to_string_t(base64Result);

	return base64String;
}

//=============================================================================
// スコアの保存処理
//=============================================================================
pplx::task<int> SaveScore(int ResultScore = 0)
{
	// NCMBの設定の再初期化
	const utility::string_t APPLICATION_KEY = U("478d418978ca1c1cc3cedbc60230ffcde8893da9ada64113b49314f3532ca8da");
	const utility::string_t CLIENT_KEY = U("a99365fcad682991c830b63db6d9d34b7b471272a2d67941852d75eeb35051de");
	const utility::string_t POST = U("POST");
	const utility::string_t SIG_API_FQDN = U("mbaas.api.nifcloud.com");
	const utility::string_t SIG_API_PATH = U("/2013-09-01/classes/");
	const utility::string_t JSON = U("application/json");

	// クラス名を指定する
	const utility::string_t className = U("Score");


	// タイムスタンプの取得
	utility::datetime now = utility::datetime::utc_now();

	//utility::string_t型に変換
	utility::string_t date = now.to_string(utility::datetime::ISO_8601);

	//std::string型に変換
	std::string dateString = utility::conversions::to_utf8string(date);

	std::replace(dateString.begin(), dateString.end(), ' ', 'T');	// 空白を "T" に置換

	//utility::string_t型に変換
	utility::string_t utdate = utility::conversions::to_string_t(dateString);

	//utdateの文字数が24より少ない時0で埋める
	if (utdate.size() < 24) 
	{
		utdate = utility::string_t(24 - utdate.size(), U('0')) + utdate;
	}

	//dateの後ろから10文字消して一番後ろにZを付けて"yyyy-MM-ddTHH:mm:ssZ"にする
	utdate.erase(utdate.size() - 9);
	utdate.push_back(U('Z')); // タイムゾーンを表す "Z" を追加

	//:を%3Aに変換する
	utdate.replace(utdate.find(U(':')), 1, U("%3A"));
	utdate.replace(utdate.find(U(':')), 1, U("%3A"));

	// シグネチャ文字列の作成
	utility::string_t sig_char = utility::conversions::to_string_t("");
	sig_char += utility::conversions::to_string_t("SignatureMethod=HmacSHA256") + utility::conversions::to_string_t("&");
	sig_char += utility::conversions::to_string_t("SignatureVersion=2") + utility::conversions::to_string_t("&");
	sig_char += utility::conversions::to_string_t("X-NCMB-Application-Key=") + utility::conversions::to_string_t(APPLICATION_KEY) + utility::conversions::to_string_t("&");
	sig_char += utility::conversions::to_string_t("X-NCMB-Timestamp=") + utdate;


	// 認証データの作成
	utility::string_t signature = U("");
	signature += POST + U("\n");
	signature += SIG_API_FQDN + U("\n");
	signature += SIG_API_PATH + className + U("\n");
	signature += sig_char;

	// 認証データをBase64に変換
	utility::string_t signatureHash = GetHMACAsBase64(signature, CLIENT_KEY);

	// URLをエンコード
	utility::string_t url = U("https://") + SIG_API_FQDN + SIG_API_PATH + className;

	// HTTPクライアントを初期化
	http_client_config clientConfig;
	clientConfig.set_timeout(std::chrono::seconds(10));
	http_client client(url, clientConfig);

	// リクエストヘッダーの設定
	http_request request;
	request.set_method(POST);
	request.headers().add(U("X-NCMB-Application-Key"), APPLICATION_KEY);
	request.headers().add(U("X-NCMB-Signature"), signatureHash);
	request.headers().add(U("X-NCMB-Timestamp"), utdate);
	request.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	request.headers().set_content_type(JSON);

	// リクエストボディの設定
	json::value content;
	content[U("Score")] = ResultScore;
	request.set_body(content);

	// リクエストを送信し、レスポンスを受け取る
	return client.request(request)
		.then([](http_response response)
	{
		// レスポンスを処理する
		if (response.status_code() == status_codes::OK)
		{
			// 成功時の処理
			return 0;
		}
		else
		{
			// エラー時の処理
			std::wcout << U("エラーが発生しました: ") << response.reason_phrase() << std::endl;
			return 2;
		}
	})
		.then([](pplx::task<int> previousTask)
	{
		// エラーハンドリング
		try
		{
			return previousTask.get();
		}
		catch (const std::exception& ex)
		{
			std::cout << "エラーが発生しました: " << ex.what() << std::endl;
			return 2;
		}
	});
}

//=============================================================================
// スコアの取得処理
//=============================================================================
pplx::task<std::vector<int>> getScore(int ResultScore = 0)
{
	// NCMBの設定の再初期化
	const utility::string_t APPLICATION_KEY = U("478d418978ca1c1cc3cedbc60230ffcde8893da9ada64113b49314f3532ca8da");
	const utility::string_t CLIENT_KEY = U("a99365fcad682991c830b63db6d9d34b7b471272a2d67941852d75eeb35051de");
	const utility::string_t POST = U("GET");
	const utility::string_t SIG_API_FQDN = U("mbaas.api.nifcloud.com");
	const utility::string_t SIG_API_PATH = U("/2013-09-01/classes/");
	const utility::string_t JSON = U("application/json");

	// クラス名を指定する
	const utility::string_t className = U("Score");


	// タイムスタンプの取得
	utility::datetime now = utility::datetime::utc_now();

	//utility::string_t型に変換
	utility::string_t date = now.to_string(utility::datetime::ISO_8601);

	//std::string型に変換
	std::string dateString = utility::conversions::to_utf8string(date);

	std::replace(dateString.begin(), dateString.end(), ' ', 'T');	// 空白を "T" に置換
	//date.replace(dateString.find(U(' ')), 1, U("T")); // 空白を "T" に置換

	//utility::string_t型に変換
	utility::string_t utdate = utility::conversions::to_string_t(dateString);

	//utdateの文字数が24より少ない時0で埋める
	if (utdate.size() < 24)
	{
		utdate = utility::string_t(24 - utdate.size(), U('0')) + utdate;
	}

	//dateの後ろから10文字消して一番後ろにZを付けて"yyyy-MM-ddTHH:mm:ssZ"にする
	utdate.erase(utdate.size() - 9);
	utdate.push_back(U('Z'));
	//date += U("Z"); // タイムゾーンを表す "Z" を追加

	//std::replace(utdate.begin(), utdate.end(), U(':'), U('%3A'));
	utdate.replace(utdate.find(U(':')), 1, U("%3A"));
	utdate.replace(utdate.find(U(':')), 1, U("%3A"));

	// シグネチャ文字列の作成
	utility::string_t sig_char = utility::conversions::to_string_t("");
	sig_char += utility::conversions::to_string_t("SignatureMethod=HmacSHA256") + utility::conversions::to_string_t("&");
	sig_char += utility::conversions::to_string_t("SignatureVersion=2") + utility::conversions::to_string_t("&");
	sig_char += utility::conversions::to_string_t("X-NCMB-Application-Key=") + utility::conversions::to_string_t(APPLICATION_KEY) + utility::conversions::to_string_t("&");
	sig_char += utility::conversions::to_string_t("X-NCMB-Timestamp=") + utdate;


	// 認証データの作成
	utility::string_t signature = U("");
	signature += POST + U("\n");
	signature += SIG_API_FQDN + U("\n");
	signature += SIG_API_PATH + className + U("\n");
	signature += sig_char;

	// 認証データをBase64に変換
	utility::string_t signatureHash = GetHMACAsBase64(signature, CLIENT_KEY);

	// URLをエンコード
	utility::string_t url = U("https://") + SIG_API_FQDN + SIG_API_PATH + className;

	// HTTPクライアントを初期化
	http_client_config clientConfig;
	clientConfig.set_timeout(std::chrono::seconds(10));
	http_client client(url, clientConfig);

	// リクエストヘッダーの設定
	http_request request;
	request.set_method(POST);
	request.headers().add(U("X-NCMB-Application-Key"), APPLICATION_KEY);
	request.headers().add(U("X-NCMB-Signature"), signatureHash);
	request.headers().add(U("X-NCMB-Timestamp"), utdate);
	request.headers().add(U("Access-Control-Allow-Origin"), U("*"));

	// リクエストを送信し、レスポンスを受け取る
	// レスポンスを受け取る
	return client.request(request)
		.then([](http_response response) -> pplx::task<std::vector<int>>
		{
			// レスポンスを処理する
		if (response.status_code() == status_codes::OK)
		{
			// レスポンスのJSONデータを取得
			web::json::value jsonResponse = response.extract_json().get();

			// "results"キーの配列を取得
			web::json::array resultsArray = jsonResponse[U("results")].as_array();

			// "Score"の値を格納するベクター
			std::vector<int> scores;

			// 各オブジェクトから"Score"の値を取得してベクターに追加
			for (const auto& result : resultsArray)
			{
				int score = result.at(U("Score")).as_integer();
				scores.push_back(score);
			}

			// スコアを降順にソート
			std::sort(scores.begin(), scores.end(), std::greater<int>());

			// scoresの要素数が10より多い場合、要素数を10に制限する
			if (scores.size() > 10)
			{
				scores.resize(10);
			}

			return pplx::task_from_result(scores);
		}
		else
		{
			// エラー時の処理
			std::wcout << U("エラーが発生しました: ") << response.reason_phrase() << std::endl;
			return pplx::task_from_result(std::vector<int>()); // エラーの場合は空のベクターを返す
		}
		})
		.then([](pplx::task<std::vector<int>> previousTask) -> std::vector<int>
		{
		// エラーハンドリング
		try
		{
			return previousTask.get();
		}
		catch (const std::exception& ex)
		{
			std::cout << "エラーが発生しました: " << ex.what() << std::endl;
			return std::vector<int>(); // エラーの場合は空のベクターを返す
		}
		});
}

//=============================================================================
// メイン処理
//=============================================================================
int main() 
{
	//スコアを保存
	pplx::task<int> saveScoreTask = SaveScore(100);
	saveScoreTask.wait();

	//スコアを取得
	auto task = getScore();
	std::vector<int> result = task.get();

	// resultの要素数を取得
	size_t resultSize = result.size();

	// int配列を宣言して0で初期化
	int resultArray[10] = { 0 };

	// resultの要素をコピー
	for (size_t i = 0; i < resultSize; i++)
	{
		resultArray[i] = result[i];
	}

	return 0;
}
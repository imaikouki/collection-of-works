//=============================================================================
//
// NCMBへHTTPリクエスト処理[PostNCMB.cs]
// Author : Imai
//
//=============================================================================
using System;
using System.Text;
using System.Security.Cryptography;
using System.Net;
using System.IO;
using System.Linq;
using UnityEngine;
using UnityEngine.UI;

public class PostNCMB : MonoBehaviour
{
    /// <summary>
    /// NCMBの設定の初期化
    /// </summary>
    private static readonly string APPLICATION_KEY = "5f2c3b04e5f2dbf94d927fd50938bd4e74f1e6a37614dbe4990ceec24e6af9a6";
    private static readonly string CLIENT_KEY = "41152d099e14c849585307f81d57b0efb67d2aee30b10a4f4b94ee254541d6d5";
    private static string POST = "POST";
    private static readonly string SIG_API_FQDN = "mbaas.api.nifcloud.com";
    private static readonly string SIG_API_PATH = "/2013-09-01/classes/";
    private static readonly string JSON = "application/json";

    [SerializeField]
    private Text voicetext;


    //=============================================================================
    // ボタンを押された時の処理
    //=============================================================================
    public void OnClick()
    {
        string voiceText = "\"" + voicetext.text + "\"";
        SaveVoiceText(voiceText);
    }

    public static void SaveVoiceText(string voiceText)
    {
        //POSTの設定
        POST = "POST";

        // クラス名を指定する
        string className = "VoiceText";

        // タイムスタンプの取得
        string date = DateTime.UtcNow.ToString("yyyy-MM-ddTHH:mm:ssZ");
        date = date.Replace(":", "%3A");

        // シグネチャ文字列の作成
        string sig_char = "";
        sig_char += "SignatureMethod=HmacSHA256" + "&";
        sig_char += "SignatureVersion=2" + "&";
        sig_char += "X-NCMB-Application-Key=" + APPLICATION_KEY + "&";
        sig_char += "X-NCMB-Timestamp=" + date;

        // 認証データの作成
        string signature = "";
        signature += POST + "\n";
        signature += SIG_API_FQDN + "\n";
        signature += SIG_API_PATH + className + "\n";
        signature += sig_char;

        // 認証データをBase64に変換
        string signatureHash = GetHMACAsBase64(signature, CLIENT_KEY);

        // URLをエンコード
        Uri url = new Uri("https://" + SIG_API_FQDN + SIG_API_PATH + className);

        // WebRequestインスタンスを初期化
        HttpWebRequest req = (HttpWebRequest)WebRequest.Create(url);

        // タイムアウトの設定
        req.Timeout = 10000;

        // リクエストに使用するメソッドの設定
        req.Method = POST;

        // Content-Typeの設定
        req.ContentType = JSON;

        // HTTPヘッダーの設定
        req.Headers.Add("X-NCMB-Application-Key", APPLICATION_KEY);
        req.Headers.Add("X-NCMB-Signature", signatureHash);
        req.Headers.Add("X-NCMB-Timestamp", date);
        req.Headers.Add("Access-Control-Allow-Origin", "*");

        //登録する情報の設定
        string content = "{\"VoiceText\"" + ":" + voiceText.ToString() + "}";

        // 登録する情報ををBase64に変換
        byte[] postDataBytes = Encoding.UTF8.GetBytes(content);

        // リクエストを書き込む
        Stream stream = null;
        try
        {//成功時
            stream = req.GetRequestStream();
            stream.Write(postDataBytes, 0, postDataBytes.Length);
        }
        catch (System.Exception cause)
        {//エラー発生時
            Debug.Log(cause);
        }
        finally
        {//最後にストリームを閉じる
            if (stream != null)
            {
                stream.Close();
            }
        }

        // レスポンスを取得する
        HttpWebResponse httpResponse = null;
        Stream streamResponse = null;
        try
        {//成功時
            httpResponse = (HttpWebResponse)req.GetResponse();
            streamResponse = httpResponse.GetResponseStream();
            Debug.Log(httpResponse);
        }
        catch (System.Exception ex)
        {//エラー発生時
            Debug.Log("エラーが発生しました: " + ex.Message);
        }
    }

    //=============================================================================
    // NCMBのシグネチャ生成処理
    //=============================================================================
    private static string GetHMACAsBase64(string _stringData, string _clientKey)
    {
        byte[] secretKeyBArr = Encoding.UTF8.GetBytes(_clientKey);
        byte[] contentBArr = Encoding.UTF8.GetBytes(_stringData);
        HMACSHA256 hmac = new HMACSHA256(secretKeyBArr);
        byte[] hashValue = hmac.ComputeHash(contentBArr);
        string hmacBase64 = Convert.ToBase64String(hashValue);
        return hmacBase64;
    }
}

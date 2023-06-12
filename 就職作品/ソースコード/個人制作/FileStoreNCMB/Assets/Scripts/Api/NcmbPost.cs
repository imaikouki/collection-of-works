//=============================================================================
//
// NCMBの通信処理[NcmbPost.cs]
// Author : Imai
//
//=============================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using NCMB;
using UnityEngine.UI;

public class NcmbPost : MonoBehaviour
{
    [SerializeField] Image image;

    // リクエストコード
    public enum ReqCode
    {
        Save = 1,   //セーブ
        Load,       //読み込み
    }

    //NCMBの呼び出し
    public void Post(ReqCode Req, string path = "", string FileName = "")
    {
        switch (Req)
        {
            case ReqCode.Save:
                SetNcmbImage(path, FileName);
                break;

            case ReqCode.Load:
                LoadNcmbImage(FileName);
                break;
        }

    }
    //NCMBのファイルストアへ保存処理
    public void SetNcmbImage(string path, string FileName)
    {
        byte[] image = File.ReadAllBytes(path);

        //画像をNCMBへ保存
        NCMBFile file = new NCMBFile(FileName, image);
        file.SaveAsync((NCMBException error) =>
        {
            if (error != null)
            {
                // 失敗
                Debug.LogWarning("保存に失敗: " + error.ErrorMessage);
            }
            else
            {
                // 成功
                Debug.Log("保存に成功");
            }
        });
    }

    //NCMBのファイルストアから読み込み
    public void LoadNcmbImage(string ImageName)
    {
        //NCMBから取得
        NCMBFile file = new NCMBFile(ImageName);
        file.FetchAsync((byte[] filedata, NCMBException error) => {
            if (error != null)
            {
                // 失敗
                Debug.Log(error);
            }
            else
            {
                //テクスチャの貼り付け
                Texture2D texture = new Texture2D(100, 100);

                texture.LoadImage(filedata);
                Rect rect = new Rect(0.0f, 0.0f, texture.width, texture.height);
                var sprite = Sprite.Create(texture, rect, Vector2.zero);
                image.sprite = sprite;
            }
        });
    }
}

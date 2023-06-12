//=============================================================================
//
// Saveボタンを押された時の処理[NcmbFileSaveIMG.cs]
// Author : Imai
//
//=============================================================================
using System.Collections;
using System.Collections.Generic;
using System.IO;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
using NCMB;

//グローバル変数を設定。
public partial class Global
{
    static public string g_filename = "";        //ファイル名
}
public class NcmbFileSaveIMG : MonoBehaviour
{
    //ボタンを押された時の処理
    public void OnClick()
    {
        Debug.Log("ファイルを開く");
        //ファイルの画面を開く
        OpenFilePanelWithFilters();   
    }

    //ファイルを開く処理
    void OpenFilePanelWithFilters()
    {
        //画像ファイルのパスだけ取得
        var path = EditorUtility.OpenFilePanelWithFilters("Select Asset", Application.dataPath, new[]{
            "Image files", "png,jpg",
        });


        //パスが返されなかった時
        if (string.IsNullOrEmpty(path))
            return;

        //ファイル名を取得
        string FileName = Path.GetFileName(path);

        //ファイル名で使えない文字の設定
        char[] invalidch = Path.GetInvalidFileNameChars();
        char[] i = { ':', '?', '#', '[', ']', '!', '$', '&', '\'', '(', ')', '*', '+', ',', ';', '=', '"', '<', '>', '%', '~', '|' };

        //使えないファイル名の置き換え
        foreach (char c in invalidch)
        {
            FileName = FileName.Replace(c, '_');
        }

        foreach (char x in i)
        {
            FileName = FileName.Replace(x, '_');
        }

        //ファイル名を保存
        Global.g_filename = FileName;

        //NCMBへ保存
        NcmbPost Post = gameObject.AddComponent<NcmbPost>();
        Post.Post(NcmbPost.ReqCode.Save, path, FileName);

        Debug.Log(FileName);
    }


}
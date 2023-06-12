//=============================================================================
//
// Loadボタンを押された時の処理[NcmbFileLoadIMG.cs]
// Author : Imai
//
//=============================================================================
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using UnityEditor;
using NCMB;

public class NcmbFileLoadIMG : MonoBehaviour
{
    NcmbPost Post;

    //ボタンを押された時の処理
    public void OnClick()
    {
        //読み込み処理の呼び出し
        Post = GetComponent<NcmbPost>();
        Post.Post(NcmbPost.ReqCode.Load, FileName: Global.g_filename);
    }
}
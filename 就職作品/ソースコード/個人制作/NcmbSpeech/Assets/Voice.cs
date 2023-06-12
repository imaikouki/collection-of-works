//=============================================================================
//
// WindowsSpeechを使用した音声認識処理[Voice.cs]
// Author : Imai
//
//=============================================================================
using UnityEditor;
using UnityEngine;
using UnityEngine.UI;
using UnityEngine.Windows.Speech;

public class Voice : MonoBehaviour
{
    [SerializeField]
    private Text DictationResult;

    [SerializeField]
    private Text Hypotheses;

    private DictationRecognizer DictationRecognizer;

    //=============================================================================
    // 初期化処理
    //=============================================================================
    void Start()
    {
        DictationRecognizer = new DictationRecognizer();

        //音声を認識し仮変換中
        DictationRecognizer.DictationResult += (text, confidence) =>
        {
            Debug.LogFormat("Dictation result: {0}", text);
            DictationResult.text = text;
        };

        //仮変換の結果が出たとき
        DictationRecognizer.DictationHypothesis += (text) =>
        {
            Debug.LogFormat("Dictation hypothesis: {0}", text);
            Hypotheses.text = text;
        };

        //音声認識が完了したとき
        DictationRecognizer.DictationComplete += (completionCause) =>
        {
            if (completionCause != DictationCompletionCause.Complete)
                Debug.LogErrorFormat("Dictation completed unsuccessfully: {0}.", completionCause);
        };

        //エラーの時
        DictationRecognizer.DictationError += (error, hresult) =>
        {
            Debug.LogErrorFormat("Dictation error: {0}; HResult = {1}.", error, hresult);
        };

        DictationRecognizer.Start();
    }
}
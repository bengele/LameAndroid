////////////////////////////////////////////////////////////////////////////////
///
/// Example
///
/// Author        :
/// Author e-mail :
/// WWW           :
///
////////////////////////////////////////////////////////////////////////////////
//
//
//
////////////////////////////////////////////////////////////////////////////////

#include "stdio.h"
#include <jni.h>
#include <android/log.h>
#include <stdexcept>
#include <string>

using namespace std;

#include "../lame/lame.h"

#define LOGV(...) __android_log_print((int)ANDROID_LOG_INFO, "mp3Lame", __VA_ARGS__)

static lame_global_flags* lame = NULL;
//#define LOGV(...)

// String for keeping possible c++ exception error messages. Notice that this isn't
// thread-safe but it's expected that exceptions are special situations that won't
// occur in several threads in parallel.
static string _errMsg = "";

#define DLL_PUBLIC __attribute__((visibility("default")))

// using namespace lame;



extern "C" DLL_PUBLIC jstring Java_com_android_lame_helper_LameHelper_getVersion(JNIEnv *env, jobject thiz)
{
    const char* version = get_lame_version();
    return env->NewStringUTF(version);
}

extern  "C" DLL_PUBLIC jboolean  Java_com_android_lame_helper_LameHelper_encodeToMp3File(JNIEnv *env,jobject thiz,jstring inputPath,jstring outputPath){
    int read,write;
    const char* inPath = (env)->GetStringUTFChars(inputPath,0);
    const char* outPath = (env)->GetStringUTFChars(outputPath,0);
    FILE *pcm = fopen(inPath,"rb");
    FILE *mp3 = fopen(outPath,"wb");

    LOGV("读取文件 pcm =%s mp3 =%s",inPath,outPath );

    if(!pcm) return false;

    int PCM_SIZE = 640;
    int MP3_SIZE = 8192;

    short int pcm_buffer[PCM_SIZE];
    unsigned char mp3_buffer[MP3_SIZE];


    LOGV("开始初始化 lame");
    if(lame == NULL){
         lame = lame_init();
         lame_set_num_channels(lame,1);
         lame_set_in_samplerate(lame,44100);
         lame_set_brate(lame,16);
         lame_set_quality(lame,5); //2最好，5:一般 7:最差
         lame_init_params(lame);
    }

    LOGV("lame初始化完毕，开始读取文件...");

    do{
        read = fread(pcm_buffer,sizeof(short int),PCM_SIZE,pcm);
        if(read == 0){
            write = lame_encode_flush(lame,mp3_buffer,MP3_SIZE);
        }else{
            write = lame_encode_buffer(lame,pcm_buffer,NULL,read,mp3_buffer,MP3_SIZE);
        }
        fwrite(mp3_buffer,write,1,mp3);
    }while (read !=0);

    LOGV("pcm文件转换完毕，关闭文件流");

    lame_close(lame);
    fclose(mp3);
    fclose(pcm);
    return true;
}


extern  "C" DLL_PUBLIC jbyteArray Java_com_android_lame_helper_LameHelper_encode(JNIEnv* env,jobject obj,jbyteArray buffer,jint length){

    jbyte *bufferArray = (env)->GetByteArrayElements(buffer,NULL);
    int shortLength = length / 2;
    short int shortBufferArray[shortLength];
    int i ;
    for(i=0;i<shortLength;i++){
        int index = 2*i;
        shortBufferArray[i] = (bufferArray[index+1] << 8) |  ((unsigned char) bufferArray[index]);
    }

    if(lame == NULL){
         lame = lame_init();
         lame_set_num_channels(lame,1);
         lame_set_in_samplerate(lame,44100);
         lame_set_brate(lame,16);
         lame_set_quality(lame,5); //2最好，5:一般 7:最差
         lame_init_params(lame);
    }


    int mp3BufferSize = (int)(shortLength*1.5+7200);
    unsigned char mp3_buffer[mp3BufferSize];
    int encodeResult;

    //LOGV("原始数据长度：%d,short数据长度:%d",length,shortLength);

    encodeResult = lame_encode_buffer(lame, shortBufferArray, shortBufferArray, shortLength, mp3_buffer, mp3BufferSize);

    //LOGV("转码数据长度:%d",encodeResult);

    jbyteArray result = (env)->NewByteArray(encodeResult);

    (env)->SetByteArrayRegion(result, 0, encodeResult,(const jbyte *) mp3_buffer);
    (env)->ReleaseByteArrayElements(buffer, bufferArray, 0);

    //LOGV("jni转码完成，返回数据");
    return result;
}







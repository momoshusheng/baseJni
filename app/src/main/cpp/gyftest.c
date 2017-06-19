//
// Created by 龚勇峰 on 2017/6/18.
//

#include <jni.h>
#include <stdio.h>
#include <string.h>
JNIEXPORT jstring JNICALL
//访问非静态变量
Java_com_example_gyf_GyfJniTest_getNameFromC(JNIEnv *env, jobject instance) {

    //通过对象拿到Class
    jclass clz = (*env)->GetObjectClass(env, instance);
    //拿到对应属性的ID
    jfieldID fid = (*env)->GetFieldID(env, clz, "name", "Ljava/lang/String;");
    //通过属性ID拿到属性的值
    jstring jstr = (*env)->GetObjectField(env, instance, fid);

    //通过Java字符串拿到C字符串，第三个参数是一个出参，
    // 用来告诉我们GetStringUTFChars内部是否复制了一份字符串
    //如果没有复制，那么出参为isCopy，这时候就不能修改字符串的值了，
    // 因为Java中常量池中的字符串是不允许修改的（但是jstr可以指向另外一个字符串）
    char* cstr = (*env)->GetStringUTFChars(env, jstr, NULL);
    //在C层修改这个属性的值
    char res[50] = "hehe:";
    strcat(res, cstr);

    //重新生成Java的字符串，并且设置给对应的属性
    jstring jstr_new = (*env)->NewStringUTF(env, res);
    (*env)->SetObjectField(env, instance, fid, jstr_new);

    //每次GetStringUTFChars，结束的时候都有一个ReleaseStringUTFChars与之呼应
    (*env)->ReleaseStringUTFChars(env, jstr, cstr);
    return (*env)->NewStringUTF(env,"gyf");
}
//访问静态变量
JNIEXPORT void JNICALL
Java_com_example_gyf_GyfJniTest_getStaticNameFormC(JNIEnv *env, jobject instance) {

    //与上面类似，只不过是某些方法需要加上Static
    jclass  cls=(*env)->GetObjectClass(env,instance);
    jfieldID jid=(*env)->GetStaticFieldID(env,cls,"NUM","I");
    jint jit=(*env)->GetStaticIntField(env,cls,jid);
    jit++;
    (*env)->SetStaticIntField(env,cls,jid,jit);
}
//访问非晶态方法
JNIEXPORT jint JNICALL
Java_com_example_gyf_GyfJniTest_getMethodFromC(JNIEnv *env, jobject instance) {

    jclass clz = (*env)->GetObjectClass(env, instance);
    //拿到方法的ID，最后一个参数是方法的签名
    jmethodID mid = (*env)->GetMethodID(env, clz, "getAdminName", "(I)I");
    //调用该方法，最后一个是可变参数，就是调用该方法所传入的参数
    //套路是如果返回是：Call返回类型Method
    jint jInt = (*env)->CallIntMethod(env, instance, mid, 100);
    printf("output from C ： %d", jInt);
    return jInt;
}

JNIEXPORT jstring JNICALL
Java_com_example_gyf_GyfJniTest_getStaticMethodFromC(JNIEnv *env, jobject instance) {

    jclass clz = (*env)->GetObjectClass(env, instance);
    jmethodID mid = (*env)->GetStaticMethodID(env, clz, "getUUID", "()Ljava/lang/String;");

    //调用java的静态方
    // 法，拿到返回值
    jstring jstr = (*env)->CallStaticObjectMethod(env, clz, mid);
    return jstr;
}

JNIEXPORT jlong JNICALL
Java_com_example_gyf_GyfJniTest_accessConstructor(JNIEnv *env, jobject instance) {

    jclass clz_date = (*env)->FindClass(env, "java/util/Date");
    //构造方法的函数名的格式是：<init>
    //不能写类名，因为构造方法函数名都一样区分不了，只能通过参数列表（签名）区分
    jmethodID mid_Date = (*env)->GetMethodID(env, clz_date, "<init>", "()V");;

    //调用构造函数
    jobject date = (*env)->NewObject(env, clz_date, mid_Date);

    //注意签名，返回值long的属性签名是J
    jmethodID mid_getTime= (*env)->GetMethodID(env, clz_date, "getTime", "()J");
    //调用getTime方法
    jlong jtime = (*env)->CallLongMethod(env, date, mid_getTime);

    return jtime;


}
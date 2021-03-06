/*
 * Copyright 2014 Google Inc. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define GLM_FORCE_RADIANS

#include <jni.h>

#include "tango-scene-reconstructor/tango_scene_reconstructor_application.h"

static tango_scene_reconstructor::TangoSceneReconstructorApplication app;

#ifdef __cplusplus
extern "C" {
#endif
JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_tangoInitialize(
    JNIEnv* env, jobject, jobject activity) {
  JavaVM* javaVM;
  env->GetJavaVM(&javaVM);
  return app.TangoInitialize(env, activity, javaVM);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_onTangoServiceConnected(
   JNIEnv* env, jobject, jobject binder) {
 return app.OnTangoServiceConnected(env, binder);
}

JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_startPCDWorker(
    JNIEnv*, jobject) {
  app.StartPCDWorker();
}

JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_stopPCDWorker(
    JNIEnv*, jobject) {
  app.StopPCDWorker();
}

JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_tangoSetupConfig(
    JNIEnv*, jobject) {
  return app.TangoSetupConfig();
}

JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_tangoConnectCallbacks(
    JNIEnv*, jobject) {
  return app.TangoConnectCallbacks();
}

JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_tangoConnect(
    JNIEnv*, jobject) {
  return app.TangoConnect();
}

JNIEXPORT jint JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_tangoSetIntrinsicsAndExtrinsics(
    JNIEnv*, jobject) {
  return app.TangoSetIntrinsicsAndExtrinsics();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_tangoDisconnect(
    JNIEnv*, jobject) {
  app.TangoDisconnect();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_initializeGLContent(
    JNIEnv*, jobject) {
  app.InitializeGLContent();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_setViewPort(
    JNIEnv*, jobject, jint width, jint height) {
  app.SetViewPort(width, height);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_setRangeValue(
    JNIEnv*, jobject, jfloat range) {
  app.SetRangeValue(range);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_render(JNIEnv*, jobject) {
  app.Render();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_freeGLContent(
    JNIEnv*, jobject) {
  app.FreeGLContent();
}

std::string ConvertJString(JNIEnv* env, jstring str)  {
  //if ( !str ) LString();
  const jsize len = env->GetStringUTFLength(str);
  const char* strChars = env->GetStringUTFChars(str, (jboolean *)0);
  std::string Result(strChars, len);
  env->ReleaseStringUTFChars(str, strChars);
  return Result;
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_onTouchEvent(
    JNIEnv*, jobject, int touch_count, int event, float x0, float y0, float x1, float y1) {
  using namespace tango_gl;
  GestureCamera::TouchEvent touch_event = static_cast<GestureCamera::TouchEvent>(event);
  app.OnTouchEvent(touch_count, touch_event, x0, y0, x1, y1);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_setCamera(
    JNIEnv*, jobject, int camera_index) {
  using namespace tango_gl;
  GestureCamera::CameraType cam_type = static_cast<GestureCamera::CameraType>(camera_index);
  app.SetCameraType(cam_type);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_showSMMesh(
    JNIEnv*, jobject) {
  app.ShowSMMesh();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_showMSMMesh(
    JNIEnv*, jobject) {
  app.ShowMSMMesh();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_showUnOPTMesh(
    JNIEnv*, jobject) {
app.ShowUnOPTMesh();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_optimize(
    JNIEnv* env, jobject) {
app.Optimize();
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_saveToFolder(
    JNIEnv* env, jobject, jstring folder_name, int save_mode) {
std::string folder_name_s = ConvertJString(env, folder_name);
app.SaveToFolder(folder_name_s, save_mode);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_setBackgroundColorBlack(
    JNIEnv* env, jobject, jboolean on) {
app.SetBackgroundColorBlack(on);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_setGridOn(
    JNIEnv* env, jobject, jboolean on) {
app.SetGridOn(on);
}

JNIEXPORT void JNICALL
Java_bashbug_tangoscenereconstructor_JNIInterface_setOptimizationMethods (JNIEnv* env, jobject, int opt) {
app.SetOptimizationMethods(opt);
}

#ifdef __cplusplus
}
#endif

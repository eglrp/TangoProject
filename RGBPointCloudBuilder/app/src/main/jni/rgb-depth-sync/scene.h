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

#ifndef TANGO_POINT_CLOUD_SCENE_H_
#define TANGO_POINT_CLOUD_SCENE_H_

#include <memory>
#include <tango_client_api.h>  // NOLINT
#include <tango-gl/axis.h>
#include <tango-gl/camera.h>
#include <tango-gl/color.h>
#include <tango-gl/gesture_camera.h>
#include <tango-gl/grid.h>
#include <tango-gl/frustum.h>
#include <tango-gl/trace.h>
#include <tango-gl/transform.h>
#include <tango-gl/util.h>
#include <tango-gl/cube.h>
#include <tango-gl/conversions.h>

#include "rgb-depth-sync/pcd_drawable.h"

namespace rgb_depth_sync {

// Scene provides OpenGL drawable objects and renders them for visualization.
  class Scene {
  public:
    // Constructor and destructor.
    Scene();
    ~Scene();

    // Release OpenGL resources allocated.
    void FreeGLContent();

    // Setup GL view port.
    void SetViewPort(int w, int h);

    void Reset();

    // Render loop.
    // @param: cur_pose_transformation, latest pose's transformation.
    // @param: point_cloud_transformation, pose transformation at point cloud
    //         frame's timestamp.
    // @param: point_cloud_vertices, point cloud's vertices of the current point
    //         frame.
    void Render(const glm::mat4& tango_pose,
                const glm::mat4& point_cloud_transformation,
                const std::vector<float>& point_cloud_data,
                const std::vector<uint8_t>& rgb_data);

    // Set render camera's viewing angle, first person, third person or top down.
    //
    // @param: camera_type, camera type includes first person, third person and
    //         top down
    void SetCameraType(tango_gl::GestureCamera::CameraType camera_type);

    // Touch event passed from android activity. This function only support two
    // touches.
    //
    // @param: touch_count, total count for touches.
    // @param: event, touch event of current touch.
    // @param: x0, normalized touch location for touch 0 on x axis.
    // @param: y0, normalized touch location for touch 0 on y axis.
    // @param: x1, normalized touch location for touch 1 on x axis.
    // @param: y1, normalized touch location for touch 1 on y axis.
    void OnTouchEvent(int touch_count, tango_gl::GestureCamera::TouchEvent event,
                      float x0, float y0, float x1, float y1);

    void SetTrace(std::vector<glm::vec3> positions);
    void SetICPTrace(std::vector<glm::vec3> positions);
    void SetBackgroundColor(bool on);
    void SetGridOn(bool on);

  private:
    GLint viewport_x_;
    GLint viewport_y_;
    GLsizei viewport_width_;
    GLsizei viewport_height_;

    float image_plane_ratio_;

    // Camera object that allows user to use touch input to interact with.
    tango_gl::GestureCamera* gesture_camera_;

    // Device axis (in device frame of reference).
    tango_gl::Axis* axis_;

    // Device frustum.
    tango_gl::Frustum* frustum_;

    // Ground grid.
    tango_gl::Grid* grid_;

    // Trace of pose data.
    tango_gl::Trace* trace_;

    tango_gl::Trace* trace_icp_;

    // Point cloud drawale object.
    PCDDrawable* pcd_drawable_;

    bool first_;
    tango_gl::Cube* cube_;
    bool backgroundColorBlack_;
    bool draw_grid_;
  };
}  // namespace tango_point_cloud

#endif  // TANGO_POINT_CLOUD_SCENE_H_

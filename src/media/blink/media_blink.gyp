# Copyright 2014 The Chromium Authors. All rights reserved.
# Use of this source code is governed by a BSD-style license that can be
# found in the LICENSE file.

{
  'targets': [
    {
      # GN version: //media/blink
      'target_name': 'media_blink',
      'type': '<(component)',
      'dependencies': [
        '../../base/base.gyp:base',
        '../../cc/cc.gyp:cc',
        '../../cc/blink/cc_blink.gyp:cc_blink',
        '../../ui/gfx/gfx.gyp:gfx_geometry',
        '../../net/net.gyp:net',
        '../../third_party/WebKit/public/blink.gyp:blink',
        '../media.gyp:media',
        '../media.gyp:shared_memory_support',
        '../../url/url.gyp:url_lib',
      ],
      'defines': [
        'MEDIA_IMPLEMENTATION',
      ],
      # This sources list is duplicated in //media/blink/BUILD.gn
      'sources': [
        'active_loader.cc',
        'active_loader.h',
        'buffered_data_source.cc',
        'buffered_data_source.h',
        'buffered_data_source_host_impl.cc',
        'buffered_data_source_host_impl.h',
        'buffered_resource_loader.cc',
        'buffered_resource_loader.h',
        'encrypted_media_player_support.cc',
        'encrypted_media_player_support.h',
        'cache_util.cc',
        'cache_util.h',
        'null_encrypted_media_player_support.cc',
        'null_encrypted_media_player_support.h',
        'texttrack_impl.cc',
        'texttrack_impl.h',
        'video_frame_compositor.cc',
        'video_frame_compositor.h',
        'webaudiosourceprovider_impl.cc',
        'webaudiosourceprovider_impl.h',
        'webinbandtexttrack_impl.cc',
        'webinbandtexttrack_impl.h',
        'webmediaplayer_delegate.h',
        'webmediaplayer_impl.cc',
        'webmediaplayer_impl.h',
        'webmediaplayer_params.cc',
        'webmediaplayer_params.h',
        'webmediaplayer_util.cc',
        'webmediaplayer_util.h',
        'webmediasource_impl.cc',
        'webmediasource_impl.h',
        'websourcebuffer_impl.cc',
        'websourcebuffer_impl.h',
      ],
      'conditions': [
        ['OS=="android"', {
          'sources!': [
            'webmediaplayer_impl.cc',
            'webmediaplayer_impl.h',
          ],
        }],
      ],
    },
    {
      'target_name': 'media_blink_unittests',
      'type': '<(gtest_target_type)',
      'dependencies': [
        'media_blink',
        '../media.gyp:media',
        '../media.gyp:media_test_support',
        '../../base/base.gyp:base',
        '../../cc/cc.gyp:cc',
        '../../cc/blink/cc_blink.gyp:cc_blink',
        '../../net/net.gyp:net',
        '../../third_party/WebKit/public/blink.gyp:blink',
        '../../ui/gfx/gfx.gyp:gfx',
        '../../ui/gfx/gfx.gyp:gfx_geometry',
        '../../ui/gfx/gfx.gyp:gfx_test_support',
        '../../url/url.gyp:url_lib',
      ],
      'sources': [
        'buffered_data_source_host_impl_unittest.cc',
        'buffered_data_source_unittest.cc',
        'buffered_resource_loader_unittest.cc',
        'cache_util_unittest.cc',
        'mock_webframeclient.h',
        'mock_weburlloader.cc',
        'mock_weburlloader.h',
        'run_all_unittests.cc',
        'test_response_generator.cc',
        'test_response_generator.h',
        'video_frame_compositor_unittest.cc',
        'webaudiosourceprovider_impl_unittest.cc',
      ],
    },
  ]
}

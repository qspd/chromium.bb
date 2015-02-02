// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "content/common/gpu/client/gpu_memory_buffer_impl_shared_memory.h"

#include "base/numerics/safe_math.h"
#include "ui/gl/gl_bindings.h"

namespace content {

GpuMemoryBufferImplSharedMemory::GpuMemoryBufferImplSharedMemory(
    const gfx::Size& size,
    unsigned internalformat)
    : GpuMemoryBufferImpl(size, internalformat) {
}

GpuMemoryBufferImplSharedMemory::~GpuMemoryBufferImplSharedMemory() {
}

// static
void GpuMemoryBufferImplSharedMemory::AllocateSharedMemoryForChildProcess(
    const gfx::Size& size,
    unsigned internalformat,
    base::ProcessHandle child_process,
    const AllocationCallback& callback) {
  DCHECK(IsLayoutSupported(size, internalformat));
  gfx::GpuMemoryBufferHandle handle;
  base::SharedMemory shared_memory;
  if (!shared_memory.CreateAnonymous(size.GetArea() *
                                     BytesPerPixel(internalformat))) {
    handle.type = gfx::EMPTY_BUFFER;
    return;
  }
  handle.type = gfx::SHARED_MEMORY_BUFFER;
  shared_memory.GiveToProcess(child_process, &handle.handle);
  callback.Run(handle);
}

// static
bool GpuMemoryBufferImplSharedMemory::IsLayoutSupported(
    const gfx::Size& size,
    unsigned internalformat) {
  base::CheckedNumeric<int> buffer_size = size.width();
  buffer_size *= size.height();
  buffer_size *= BytesPerPixel(internalformat);
  return buffer_size.IsValid();
}

// static
bool GpuMemoryBufferImplSharedMemory::IsUsageSupported(unsigned usage) {
  switch (usage) {
    case GL_IMAGE_MAP_CHROMIUM:
      return true;
    default:
      return false;
  }
}

// static
bool GpuMemoryBufferImplSharedMemory::IsConfigurationSupported(
    const gfx::Size& size,
    unsigned internalformat,
    unsigned usage) {
  return IsLayoutSupported(size, internalformat) && IsUsageSupported(usage);
}

bool GpuMemoryBufferImplSharedMemory::Initialize() {
  DCHECK(IsLayoutSupported(size_, internalformat_));
  scoped_ptr<base::SharedMemory> shared_memory(new base::SharedMemory());
  if (!shared_memory->CreateAnonymous(size_.GetArea() *
                                      BytesPerPixel(internalformat_)))
    return false;
  shared_memory_ = shared_memory.Pass();
  DCHECK(!shared_memory_->memory());
  return true;
}

bool GpuMemoryBufferImplSharedMemory::InitializeFromHandle(
    const gfx::GpuMemoryBufferHandle& handle) {
  DCHECK(IsLayoutSupported(size_, internalformat_));
  if (!base::SharedMemory::IsHandleValid(handle.handle))
    return false;
  shared_memory_.reset(new base::SharedMemory(handle.handle, false));
  DCHECK(!shared_memory_->memory());
  return true;
}

void* GpuMemoryBufferImplSharedMemory::Map() {
  DCHECK(!mapped_);
  if (!shared_memory_->Map(size_.GetArea() * BytesPerPixel(internalformat_)))
    return NULL;
  mapped_ = true;
  return shared_memory_->memory();
}

void GpuMemoryBufferImplSharedMemory::Unmap() {
  DCHECK(mapped_);
  shared_memory_->Unmap();
  mapped_ = false;
}

uint32 GpuMemoryBufferImplSharedMemory::GetStride() const {
  return size_.width() * BytesPerPixel(internalformat_);
}

gfx::GpuMemoryBufferHandle GpuMemoryBufferImplSharedMemory::GetHandle() const {
  gfx::GpuMemoryBufferHandle handle;
  handle.type = gfx::SHARED_MEMORY_BUFFER;
  handle.handle = shared_memory_->handle();
  return handle;
}

}  // namespace content

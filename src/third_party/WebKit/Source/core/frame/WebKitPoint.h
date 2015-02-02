/*
 * Copyright (C) 2009 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef WebKitPoint_h
#define WebKitPoint_h

#include "bindings/core/v8/ScriptWrappable.h"
#include "platform/heap/Handle.h"
#include "wtf/PassRefPtr.h"
#include "wtf/RefCounted.h"

namespace blink {

class WebKitPoint FINAL : public RefCountedWillBeGarbageCollected<WebKitPoint>, public ScriptWrappable {
public:
    static PassRefPtrWillBeRawPtr<WebKitPoint> create()
    {
        return adoptRefWillBeNoop(new WebKitPoint());
    }
    static PassRefPtrWillBeRawPtr<WebKitPoint> create(float x, float y)
    {
        return adoptRefWillBeNoop(new WebKitPoint(x, y));
    }

    float x() const { return m_x; }
    float y() const { return m_y; }

    void setX(float x) { m_x = x; }
    void setY(float y) { m_y = y; }

    void trace(Visitor*) { }

private:
    WebKitPoint(float x = 0, float y = 0)
        : m_x(x)
        , m_y(y)
    {
        ScriptWrappable::init(this);
    }

    float m_x;
    float m_y;
};

} // namespace blink

#endif // WebKitPoint_h

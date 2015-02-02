// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef TrackListBase_h
#define TrackListBase_h

#include "core/events/EventTarget.h"

#include "core/html/HTMLMediaElement.h"
#include "core/html/track/TrackEvent.h"

namespace blink {

template<class T>
class TrackListBase : public RefCountedWillBeRefCountedGarbageCollected<TrackListBase<T> >, public EventTargetWithInlineData {
    REFCOUNTED_EVENT_TARGET(TrackListBase);
    WILL_BE_USING_GARBAGE_COLLECTED_MIXIN(TrackListBase);
public:
    explicit TrackListBase(HTMLMediaElement* mediaElement)
        : m_mediaElement(mediaElement)
    {
    }

    virtual ~TrackListBase()
    {
#if !ENABLE(OILPAN)
        ASSERT(m_tracks.isEmpty());
        ASSERT(!m_mediaElement);
#endif
    }

    unsigned length() const { return m_tracks.size(); }
    T* anonymousIndexedGetter(unsigned index) const
    {
        if (index >= m_tracks.size())
            return 0;
        return m_tracks[index].get();
    }

    T* getTrackById(const String& id) const
    {
        for (unsigned i = 0; i < m_tracks.size(); ++i) {
            if (m_tracks[i]->id() == id)
                return m_tracks[i].get();
        }

        return 0;
    }

    DEFINE_ATTRIBUTE_EVENT_LISTENER(change);
    DEFINE_ATTRIBUTE_EVENT_LISTENER(addtrack);
    DEFINE_ATTRIBUTE_EVENT_LISTENER(removetrack);

    // EventTarget interface
    virtual ExecutionContext* executionContext() const OVERRIDE
    {
        if (m_mediaElement)
            return m_mediaElement->executionContext();
        return 0;
    }

#if !ENABLE(OILPAN)
    void shutdown()
    {
        removeAll();
        m_mediaElement = nullptr;
    }
#endif

    void add(PassRefPtrWillBeRawPtr<T> prpTrack)
    {
        RefPtrWillBeRawPtr<T> track = prpTrack;

        track->setMediaElement(m_mediaElement);
        m_tracks.append(track);
        scheduleTrackEvent(EventTypeNames::addtrack, track.release());
    }

    void remove(blink::WebMediaPlayer::TrackId trackId)
    {
        for (unsigned i = 0; i < m_tracks.size(); ++i) {
            if (m_tracks[i]->trackId() != trackId)
                continue;

            m_tracks[i]->setMediaElement(0);
            scheduleTrackEvent(EventTypeNames::removetrack, m_tracks[i]);
            m_tracks.remove(i);
            return;
        }
        ASSERT_NOT_REACHED();
    }

    void removeAll()
    {
        for (unsigned i = 0; i < m_tracks.size(); ++i)
            m_tracks[i]->setMediaElement(0);

        m_tracks.clear();
    }

    void scheduleChangeEvent()
    {
        RefPtrWillBeRawPtr<Event> event = Event::create(EventTypeNames::change);
        event->setTarget(this);
        m_mediaElement->scheduleEvent(event);
    }

    Node* owner() const { return m_mediaElement; }

    void trace(Visitor* visitor)
    {
        visitor->trace(m_tracks);
        visitor->trace(m_mediaElement);
        EventTargetWithInlineData::trace(visitor);
    }

private:
    void scheduleTrackEvent(const AtomicString& eventName, PassRefPtrWillBeRawPtr<T> track)
    {
        TrackEventInit initializer;
        initializer.track = track;
        initializer.bubbles = false;
        initializer.cancelable = false;
        RefPtrWillBeRawPtr<Event> event = TrackEvent::create(eventName, initializer);
        event->setTarget(this);
        m_mediaElement->scheduleEvent(event);
    }

    WillBeHeapVector<RefPtrWillBeMember<T> > m_tracks;
    RawPtrWillBeMember<HTMLMediaElement> m_mediaElement;
};

}

#endif

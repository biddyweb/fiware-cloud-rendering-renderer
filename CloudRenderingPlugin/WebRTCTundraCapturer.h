
// For conditions of distribution and use, see copyright notice in LICENSE

#pragma once

#include "CloudRenderingPluginApi.h"
#include "CloudRenderingPluginFwd.h"
#include "WebRTCRenderer.h"

#include <QObject>

#include "talk/media/base/videocommon.h"
#include "talk/media/base/videocapturer.h"
#include "talk/base/timeutils.h"

namespace WebRTC
{
    class TundraCapturer : public QObject, 
                           public cricket::VideoCapturer, 
                           public TundraRendererConsumer
    {
        Q_OBJECT

    public:
        TundraCapturer(Framework *framework);
        ~TundraCapturer();
        
        /// cricket::VideoCapturer overrides.
        cricket::CaptureState Start(const cricket::VideoFormat& capture_format);
        void Stop();
        bool IsRunning();
        bool IsScreencast() const;
        
        /// TundraRendererConsumer implementation
        void OnTundraFrame(const QImage *frame);
        
    protected:
        /// cricket::VideoCapturer overrides.
        bool GetPreferredFourccs(std::vector<uint32>* fourccs);
        
    private slots:
        void OnPostUpdate(float frametime);
        
    private:
        Framework *framework_;
        bool running_;
        
        shared_ptr<TundraCapturer> selfShared_;
        
        uint64 time_;
    };
}

/*
 *      Copyright (C) 2005-2008 Team XBMC
 *      http://www.xbmc.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with XBMC; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#ifndef _OMX_PLAYERVIDEO_H_
#define _OMX_PLAYERVIDEO_H_

#include "DllAvUtil.h"
#include "DllAvFormat.h"
#include "DllAvFilter.h"
#include "DllAvCodec.h"

#include "OMXReader.h"
#include "OMXClock.h"
#include "OMXStreamInfo.h"
#include "OMXVideo.h"
#ifdef STANDALONE
#include "OMXThread.h"
#else
#include "threads/Thread.h"
#endif

#include <deque>
#include <sys/types.h>

#include <string>

#include <QObject>

class OMX_TextureProvider;
class OMX_VideoSurfaceElement;

using namespace std;

#ifdef STANDALONE
class OMXPlayerVideo : public QObject, public OMXThread
#else
class OMXPlayerVideo : public CThread
#endif
{
    Q_OBJECT
protected:
  AVStream                  *m_pStream;
  int                       m_stream_id;
  std::deque<OMXPacket *>   m_packets;
  DllAvUtil                 m_dllAvUtil;
  DllAvCodec                m_dllAvCodec;
  DllAvFormat               m_dllAvFormat;
  bool                      m_open;
  COMXStreamInfo            m_hints;
  double                    m_iCurrentPts;
  pthread_cond_t            m_packet_cond;
  pthread_cond_t            m_picture_cond;
  pthread_mutex_t           m_lock;
  pthread_mutex_t           m_subtitle;
  pthread_mutex_t           m_lock_decoder;
  pthread_mutex_t           m_lock_subtitle;
  OMXClock                  *m_av_clock;
  COMXVideo                 *m_decoder;
  float                     m_fps;
  double                    m_frametime;
  bool                      m_Deinterlace;
  float                     m_display_aspect;
  //CRect                     m_DestRect;
  bool                      m_bMpeg;
  bool                      m_bAbort;
  bool                      m_use_thread;
  bool                      m_flush;
  unsigned int              m_cached_size;
  unsigned int              m_max_data_size;
  float                     m_fifo_size;
  bool                      m_hdmi_clock_sync;
  double                    m_iVideoDelay;
  double                    m_pts;
  bool                      m_syncclock;
  int                       m_speed;
  double                    m_FlipTimeStamp; // time stamp of last flippage. used to play at a forced framerate
  OMX_TextureProvider*      m_provider;

  void Lock();
  void UnLock();
  void LockDecoder();
  void UnLockDecoder();  
private:
public:
  OMXPlayerVideo(OMX_TextureProvider* provider);
  virtual ~OMXPlayerVideo();
//  bool Open(Open(COMXStreamInfo &hints, OMXClock *av_clock, const CRect& DestRect, bool deinterlace, bool mpeg, bool hdmi_clock_sync, bool use_thread,
//                             float display_aspect, float queue_size, float fifo_size);
  bool Open(COMXStreamInfo &hints, OMXClock *av_clock, OMX_TextureData*& textureData, bool deinterlace, bool mpeg, bool hdmi_clock_sync, bool use_thread,
                               float display_aspect, float queue_size, float fifo_size);

  bool Close();
  void Output(double pts);
  bool Decode(OMXPacket *pkt);
  void Process();
  void Flush();
  bool AddPacket(OMXPacket *pkt);
  bool OpenDecoder(OMX_TextureData*& textureData);
  bool CloseDecoder();
  int  GetDecoderBufferSize();
  int  GetDecoderFreeSpace();
  double GetCurrentPTS() { return m_pts; };
  double GetFPS() { return m_fps; };
  unsigned int GetCached() { return m_cached_size; };
  unsigned int GetMaxCached() { return m_max_data_size; };
  unsigned int GetLevel() { return m_max_data_size ? 100 * m_cached_size / m_max_data_size : 0; };
  void  WaitCompletion();
  void SetDelay(double delay) { m_iVideoDelay = delay; }
  double GetDelay() { return m_iVideoDelay; }
  void SetSpeed(int iSpeed);
};
#endif

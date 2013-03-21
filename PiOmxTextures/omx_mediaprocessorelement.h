/*
 * Project: PiOmxTextures
 * Author:  Luca Carlon
 * Date:    11.01.2012
 *
 * Copyright (c) 2012, 2013 Luca Carlon. All rights reserved.
 *
 * This file is part of PiOmxTextures.
 *
 * PiOmxTextures is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * PiOmxTextures is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with PiOmxTextures.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef OMX_MEDIAPROCESSORELEMENT_H
#define OMX_MEDIAPROCESSORELEMENT_H

/*------------------------------------------------------------------------------
|    includes
+-----------------------------------------------------------------------------*/
#include <QQuickItem>

#include "omx_mediaprocessor.h"


/*------------------------------------------------------------------------------
|    OMX_MediaProcessorElement class
+-----------------------------------------------------------------------------*/
class OMX_MediaProcessorElement : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
    Q_PROPERTY(bool autoplay READ autoplay WRITE setAutoplay)
    Q_PROPERTY(int volume READ volume WRITE setVolume)
public:
    explicit OMX_MediaProcessorElement(QQuickItem* parent = 0);
    ~OMX_MediaProcessorElement();

    QString source();
    void setSource(QString source);

    bool autoplay();
    void setAutoplay(bool ap);
    int volume();
    OMX_MediaProcessor* mediaProcessor() {
        return m_mediaProc;
    }

public slots:
    Q_INVOKABLE bool play();
    Q_INVOKABLE bool stop();
    Q_INVOKABLE bool pause();
    Q_INVOKABLE bool seek(long millis);
    Q_INVOKABLE long currentPosition();
    Q_INVOKABLE bool setVolume(long volume);

signals:
    void textureReady(const OMX_TextureData* textureId);
    void textureInvalidated();
    void sourceChanged(QString filepath);

    void playbackStarted();
    void playbackCompleted();

protected:
    QSGNode* updatePaintNode(QSGNode*, UpdatePaintNodeData*);

private:
    OMX_MediaProcessor* m_mediaProc;
    OMX_TextureProvider* m_texProvider;

    QString m_source;
    volatile bool m_pendingOpen;
    OMX_TextureData* m_textureData;
    bool m_autoplay;

private slots:
    void instantiateMediaProcessor();
    bool openMedia(QString filepath);
};

#endif // OMX_MEDIAPROCESSORELEMENT_H

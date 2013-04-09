#include "piomxtextureplugin.h"
#include <QDebug>

extern "C" {
#include "libavformat/avformat.h"
}

#include "lgl_logging.h"
#include "omx_imageelement.h"
#include "omx_videosurfaceelement.h"
#include "omx_camerasurfaceelement.h"
#include "omx_mediaprocessorelement.h"
#include "omx_audioprocessor.h"
#include "omx_mediaprocessor.h"

void PiOmxTexturePlugin::registerTypes(const char *uri)
{
    Q_ASSERT(uri == QLatin1String("PiOmxTextures"));
    qDebug() << "In PiOmxTexturePlugin::registerTypes";
    // Registers all the codecs.
    av_register_all();


    qRegisterMetaType<GLuint>("GLuint");
    qRegisterMetaType<OMX_TextureData*>("OMX_TextureData*");
    // @uri PiOmxTextures
    qmlRegisterType<OMX_ImageElement>(uri, 1, 0, "OMXImage");
    qmlRegisterType<OMX_VideoSurfaceElement>(uri, 1, 0, "OMXVideoSurface");
    qmlRegisterType<OMX_CameraSurfaceElement>(uri, 1, 0, "OMXCameraSurface");
    qmlRegisterType<OMX_MediaProcessorElement>(uri, 1, 0, "OMXMediaProcessor");
}


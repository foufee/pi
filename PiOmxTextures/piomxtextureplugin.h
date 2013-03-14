#ifndef PIOMXTEXTUREPLUGIN_H
#define PIOMXTEXTUREPLUGIN_H

#include <QQmlExtensionPlugin>

class PiOmxTexturePlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "com.luke.qml")
public:
    void registerTypes(const char *uri);
};

#endif // PIOMXTEXTUREPLUGIN_H

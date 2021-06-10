/****************************************************************************
 *
 * @author Doniyor Tokhirov <tokhirovdoniyor(at)gmail.com>
 *
 ****************************************************************************/

#include "androidnatives.h"

#include <QtAndroidExtras/qandroidfunctions.h>
#include <QtAndroidExtras/qandroidjnienvironment.h>
#include <QtCore/qdebug.h>

void nativeSetFullscreen() {
    QAndroidJniObject activity = QtAndroid::androidActivity();
    if (activity.isValid()) {
        QAndroidJniObject window = activity.callObjectMethod("getWindow", "()Landroid/view/Window;");
        if (window.isValid()) {
            const int FLAG_KEEP_SCREEN_ON = 128;
            const int FLAG_FULLSCREEN = 1024;
            window.callMethod<void>("addFlags", "(I)V", FLAG_KEEP_SCREEN_ON | FLAG_FULLSCREEN);
            QAndroidJniEnvironment env;
            if (env->ExceptionCheck())
                env->ExceptionClear();
        }
    }
}

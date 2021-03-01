#ifndef VIDEOUTILS_H
#define VIDEOUTILS_H

#include <Irrlicht.h>

namespace Utils
{
    //! Converts an YUV color to an RBG Colour
    void convertYUVtoRBG(float& r, float& g, float& b, float y, float u, float v)
    {
        // Source: http://www.gamedev.ru/code/articles/?id=4252&page=2
        r = y + 1.371f * (v - 128);
        g = y - 0.698f * (u - 128) - 0.336f * (u - 128);
        b = y + 1.732f * (u - 128);
        if (r < 0 ) r = 0;
        if (g < 0 ) g = 0;
        if (b < 0 ) b = 0;
        if (r > 255) r = 255;
        if (g > 255) g = 255;
        if (b > 255) b = 255;

//        // Source: http://en.wikipedia.org/wiki/YUV#Y.27UV420p_.28and_Y.27V12_or_YV12.29_to_RGB888_conversion
//        r = y + (int)(1.772f * v);
//        g = y - (int)(0.344f * v + 0.714f * u);
//        b = y + (int)(1.402f * u);
//        r = (r >255) ? r=255 : (r < 0) ? 0 : r;
//        g = (g >255) ? g=255 : (g < 0) ? 0 : g;
//        b = (b >255) ? b=255 : (b < 0) ? 0 : b;

//        // Source Theora Spec
//        y = y / 255;
//        u = u / 255;
//        v = v / 255;
//        r = y + 2 * (1 - 0.229f) * v;
//        g = y - 2 * ((1 - 0.114f) * 0.114f) / (1 - 0.114f - 0.299f) * u - 2 * ((1 - 0.229f) * 0.229f) / (1 - 0.114f - 0.229f) * v;
//        b = y + 2 * (1 - 0.114f)  * u;
//        if (r < 0) r = 0;
//        if (r > 1) r = 1;
//        if (g < 0) g = 0;
//        if (g > 1) g = 1;
//        if (b < 0) b = 0;
//        if (b > 1) b = 1;
//        float alpha = 4.5f;
//        float beta = 0.45f;
//        float delta = 0.018f;
//        float epsilon = 0.099;
//        if (r >= 0 && r < delta ) r = alpha * r;
//        if (r >= delta && r <= 1) r = (1 + epsilon) * pow(r, beta) - epsilon;
//        if (g >= 0 && g < delta ) g = alpha * g;
//        if (g >= delta && g <= 1) g = (1 + epsilon) * pow(g, beta) - epsilon;
//        if (b >= 0 && b < delta ) b = alpha * b;
//        if (b >= delta && b <= 1) b = (1 + epsilon) * pow(b, beta) - epsilon;
//        r = r * 255;
//        g = g * 255;
//        b = b * 255;
    }
    //! Converts an RBG color to an YUV Colour
    void convertRGBtoYUV(float& y, float& u, float& v, float r, float g, float b)
    {
        y = 0.299f * r + 0.587f * g + 0.114f * b;
        u = b - y;
        v = r - y;
    }
}

#endif // VIDEOUTILS_H

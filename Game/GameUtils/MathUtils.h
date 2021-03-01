#ifndef MATHUTILS_H
#define MATHUTILS_H

#include <cmath>

namespace Utils
{
    // a constant which converts degrees to radians
    const float DEG2RAD = M_PI/180.0f;
    // a constant which converts radians to degrees
    const float RAD2DEG = 180.0f/M_PI;

    inline float lerpDegrees(float start, float end, float amount)
    {
        // NOTE: Source, a webforum can't remember where hence public domain (ST)
        float difference = fabsf(end - start);
        if (difference > 180.0f)
        {
            // We need to add on to one of the values.
            if (end > start)
            {
                // We'll add it on to start...
                start += 360.0f;
            }
            else
            {
                // Add it on to end.
                end += 360.0f;
            }
        }

        // Interpolate it.
        float value = (start + ((end - start) * amount));

        // Wrap it..
        float rangeZero = 360.0f;

        if (value >= 0.0f && value <= 360.0f)
            return value;

        return fmod(value, rangeZero);
    }

    inline float lerpRadians(float start, float end, float amount)
    {
        // NOTE: Source, a webforum can't remember where hence public domain (ST)
        float difference = fabsf(end - start);
        if (difference > M_PI)
        {
            // We need to add on to one of the values.
            if (end > start)
            {
                // We'll add it on to start...
                start += (2.0f * M_PI);
            }
            else
            {
                // Add it on to end.
                end += (2.0f * M_PI);
            }
        }
        // Interpolate it.
        float value = (start + ((end - start) * amount));
        // Wrap it..
        float rangeZero = (2.0f * M_PI);

        if (value >= 0.0f && value <= (2.0f * M_PI))
            return value;

        return fmod(value, rangeZero);
    }
    // Mae a random number between 0.0f and 1.0f
    inline float random()
    {
        return (float)rand() / (float)RAND_MAX;
    }
    // Make a random number between min and max
    inline float random(float min, float max)
    {
        // Make sure that min < max
        if (min > max)
        {
            // Swap min and max
            float temp = max;
            max = min;
            min = temp;
        }
        // Generate a value between 0.0f amd 1.0f;
        float value = (float)(rand()) / (float)(RAND_MAX);
        // Scale value into the range min and max
        value = value * (max - min) + min;
        // Return the value
        return value;
    }
    //! Swap two floats
    inline void swap(float& one, float& two)
    {
        float temp = two;
        two = one;
        one = temp;
    }
    //! Swap two doubles
    inline void swap(double& one, double& two)
    {
        double temp = two;
        two = one;
        one = temp;
    }
    //! Swap two ints
    inline void swap(int& one, int& two)
    {
        int temp = two;
        two = one;
        one = temp;
    }
    //! Swap two longs
    inline void swap(long& one, long& two)
    {
        long temp = two;
        two = one;
        one = temp;
    }
    //! Lerp (Linear Interpolation; t must be between 0 and 1)
    inline float lerp(float a, float b, float t)
    {
        return a * (1 - t) + b * (t);
    }
}

#endif // MATHUTILS_H

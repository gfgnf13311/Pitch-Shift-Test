#include <jni.h>
#include <cmath>
#include <vector>

// Buildable JNI placeholder. Replace this linear-resampling implementation with
// Rubber Band's real-time/study API before using it for duration-preserving pitch shift.
// This implementation demonstrates JNI linkage only and is not a Rubber Band engine.
extern "C" JNIEXPORT jlong JNICALL
Java_com_example_pitchshift_PitchShifter_nativeCreate(JNIEnv*, jobject, jint sampleRate, jint channels) {
    if (sampleRate <= 0 || channels <= 0) return 0;
    return static_cast<jlong>((sampleRate << 8) | (channels & 0xff));
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_pitchshift_PitchShifter_nativeProcess(JNIEnv* env, jobject, jlong,
        jfloatArray input, jfloatArray output, jfloat pitchRatio) {
    const jsize n = env->GetArrayLength(input);
    if (env->GetArrayLength(output) != n || n == 0 || pitchRatio <= 0.0f) return;
    std::vector<jfloat> in(n), out(n);
    env->GetFloatArrayRegion(input, 0, n, in.data());
    // Placeholder only: resampling changes duration/pitch and is not Rubber Band.
    for (jsize i = 0; i < n; ++i) {
        double src = std::fmod(static_cast<double>(i) * pitchRatio, static_cast<double>(n));
        jsize idx = static_cast<jsize>(src);
        jsize next = (idx + 1) % n;
        float frac = static_cast<float>(src - idx);
        out[i] = in[idx] * (1.0f - frac) + in[next] * frac;
    }
    env->SetFloatArrayRegion(output, 0, n, out.data());
}

extern "C" JNIEXPORT void JNICALL
Java_com_example_pitchshift_PitchShifter_nativeDestroy(JNIEnv*, jobject, jlong) {}

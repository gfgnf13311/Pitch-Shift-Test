# PitchShift Video — Android starter

This is a starter Android Studio project with:
- Kotlin UI to select a video and choose a pitch from -12 to +12 semitones.
- A JNI/CMake shared library so native loading and Android ABI builds are demonstrated.
- A GitHub Actions workflow that builds a **debug APK** and uploads it as an Actions artifact.

## Important status

**This is a buildable starter scaffold, not a finished video pitch-shifter yet.** The current native code is a clearly marked placeholder and does not use Rubber Band. The Export MP4 button explains this instead of creating a misleading output.

To make the requested feature real, the next implementation steps are:
1. Add the Rubber Band Library source or Android-built `.so`/headers and its required dependencies/licensing notices.
2. Replace the placeholder methods in `app/src/main/cpp/pitchshift.cpp` with Rubber Band's supported C/C++ API, including correct streaming/finalization and channel handling.
3. Decode the selected video's audio to PCM, process it in chunks, encode the shifted audio, and mux it with the original video stream while preserving timestamps. Android `MediaExtractor`, `MediaCodec`, and `MediaMuxer` can do this, but it requires a complete pipeline; it is not implemented in this scaffold.
4. Add tests for duration, synchronization, mono/stereo, and device ABI support.

The provided `PitchShifter.kt` preserves the Kotlin interface shape from the request. The placeholder native resampling code changes duration and is not a substitute for Rubber Band's pitch-preserving algorithm.

## Build locally

Open this folder in Android Studio (recent version with JDK 17 support), allow Gradle sync, then run the `app` configuration. Alternatively, with Gradle installed:

```bash
gradle assembleDebug
```

The APK output is `app/build/outputs/apk/debug/app-debug.apk`.

## Build with GitHub Actions

1. Create a GitHub repository.
2. Upload/push all files from this folder to the repository's `main` branch.
3. Open **Actions** → **Android APK**. It runs on pushes and can also be started with **Run workflow**.
4. Open the successful workflow run, then download `pitchshift-video-debug-apk` from **Artifacts**.
5. Extract the downloaded artifact ZIP to get `app-debug.apk`.

The artifact is a debug APK intended for testing, not a signed Play Store release.

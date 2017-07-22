# rm -rf libs
# rm -rf obj
mv Red3DEngine jni
ndk-build
mv jni Red3DEngine

rm -rf Red3DEngineAndroid/app/src/main/jniLibs
cp -r libs Red3DEngineAndroid/app/src/main/

mv Red3DEngineAndroid/app/src/main/libs Red3DEngineAndroid/app/src/main/jniLibs

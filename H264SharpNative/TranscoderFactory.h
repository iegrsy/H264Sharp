#ifndef TRANSCODER_FACTORY
#define TRANSCODER_FACTORY
#include "Encoder.h"
#include "Decoder.h"
using namespace H264Sharp;

#ifdef __cplusplus
extern "C" {
#endif

#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_EXPORT __attribute__((dllexport))
#else
#define DLL_EXPORT __declspec(dllexport)
#endif
#else
#if __GNUC__ >= 4
#define DLL_EXPORT __attribute__((visibility("default")))
#else
#define DLL_EXPORT
#endif
#endif
    using namespace H264Sharp;
    /////////////////Encoder/////////////////////////////////

    DLL_EXPORT int Hello() {
        return 42;
    }

    DLL_EXPORT H264Sharp::Encoder* GetEncoder(const char* dllname) {
        return new H264Sharp::Encoder(dllname);
    }

    DLL_EXPORT int InitializeEncoder(Encoder* encoder, int width, int height, int bps, int fps, int configType) {
        return encoder->Initialize(width, height, bps, fps, static_cast<ConfigType>(configType));
    }

    DLL_EXPORT int GetDefaultParams(Encoder* encoder, SEncParamExt* params) {
        return encoder->GetDefaultParams(*params);
    }

    DLL_EXPORT int InitializeEncoderBase(Encoder* encoder, SEncParamBase params) {
        return encoder->Initialize(params);
    }

    DLL_EXPORT int InitializeEncoder2(Encoder* encoder, SEncParamExt params) {
        return encoder->Initialize(params);
    }

    DLL_EXPORT bool Encode(Encoder* encoder, GenericImage* img, FrameContainer* fc) {
        return encoder->Encode(*img, *fc);
    }

    DLL_EXPORT bool Encode1(Encoder* encoder, byte* yuv, FrameContainer* fc) {
        return encoder->Encode(yuv, *fc);
    }

    DLL_EXPORT int ForceIntraFrame(Encoder* encoder) {
        return encoder->ForceIntraFrame();
    }

    DLL_EXPORT void SetMaxBitrate(Encoder* encoder, int target) {
        encoder->SetMaxBitrate(target);
    }

    DLL_EXPORT void SetTargetFps(Encoder* encoder, float target) {
        encoder->SetTargetFps(target);
    }

    DLL_EXPORT void SetParallelConverterEnc(Encoder* encoder, int threadCount) {
        encoder->threadCount = threadCount;
    }

    DLL_EXPORT void FreeEncoder(Encoder* encoder) {
        delete encoder;
    }

    DLL_EXPORT int SetOptionEncoder(Encoder* encoder, ENCODER_OPTION option, void* value) {
        return encoder->SetOption(option, value);
    }

    DLL_EXPORT int GetOptionEncoder(Encoder* encoder, ENCODER_OPTION option, void* value) {
        return encoder->GetOption(option, value);
    }

    //----------------------Decoder--------------------------------------------------------

    DLL_EXPORT Decoder* GetDecoder(const char* dllname) {
        return new Decoder(dllname);
    }

    DLL_EXPORT int InitializeDecoderDefault(Decoder* decoder) {
        return decoder->Initialize();
    }

    DLL_EXPORT int InitializeDecoder(Decoder* decoder, SDecodingParam decParam) {
        return decoder->Initialize(decParam);
    }

    DLL_EXPORT bool DecodeAsYUV(Decoder* decoder, unsigned char* frame, int length, bool noDelay, DecodingState* state, Yuv420p* decoded) {
        return decoder->Decode(frame, length, noDelay, *state, *decoded);
    }

    DLL_EXPORT bool DecodeAsRGB(Decoder* decoder, unsigned char* frame, int length, bool noDelay, DecodingState* state, RgbImage* decoded) {
        return decoder->Decode(frame, length, noDelay, *state, *decoded);
    }

    DLL_EXPORT bool DecodeAsRGBInto(Decoder* decoder, unsigned char* frame, int length, bool noDelay, DecodingState* state, unsigned char* decoded) {
        return decoder->DecodeExt(frame, length, noDelay, *state, decoded);
    }

    DLL_EXPORT bool DecodeAsRGBInto2(int a) {
        return true;
    }

    DLL_EXPORT void FreeDecoder(Decoder* decoder) {
        delete decoder;
    }

    DLL_EXPORT void SetParallelConverterDec(Decoder* decoder, int threadCount) {
        decoder->threadCount = threadCount;
    }

    DLL_EXPORT void UseSSEYUVConverter(Decoder* decoder, bool isSSE) {
        decoder->UseSSEConverter(isSSE);
    }

    DLL_EXPORT int SetOptionDecoder(Decoder* decoder, DECODER_OPTION option, void* value) {
        return decoder->SetOption(option, value);
    }

    DLL_EXPORT int GetOptionDecoder(Decoder* decoder, DECODER_OPTION option, void* value) {
        return decoder->GetOption(option, value);
    }

    //-----

    DLL_EXPORT void YUV420ToRGB(Yuv420p* from, RgbImage* to, int threadCount) {
        Yuv420P2RGB(to->ImageBytes, from->Y, from->U, from->V, to->Width, to->Height, from->strideY, from->strideU, to->Width * 3, true, threadCount);
    }

    DLL_EXPORT void RGB2YUV420(RgbImage* from, Yuv420p* to, int threadCount) {
        RGBtoYUV420Planar(from->ImageBytes, to->Y, from->Width, from->Height, from->Stride, threadCount);
    }

    DLL_EXPORT void DownscaleImg(GenericImage* from, GenericImage* to, int multiplier) {
        ImageType imtype = from->Type;
        switch (imtype) {
        case ImageType::Rgb:
        case ImageType::Bgr:
            Downscale24(from->ImageBytes, from->Width, from->Height, from->Stride, to->ImageBytes, multiplier);
            break;

        default:
            Downscale32(from->ImageBytes, from->Width, from->Height, from->Stride, to->ImageBytes, multiplier);
            break;
        }
    }

#ifdef __cplusplus
}
#endif

//#pragma once
//#include "pch.h";
//#include "Encoder.h"
//#include "Decoder.h"
//using namespace H264Sharp;
//
//
//	/////////////////Encoder/////////////////////////////////
//
//	extern "C" __declspec(dllexport)  int __cdecl Hello()
//	{
//		return 42;
//	}
//
//	extern "C" __declspec(dllexport)  H264Sharp::Encoder * __cdecl GetEncoder(const wchar_t* dllname)
//	{
//		return new H264Sharp::Encoder(dllname);
//	}
//
//	extern "C" __declspec(dllexport)  int __cdecl InitializeEncoder(Encoder* encoder,int width, int height, int bps, int fps, int configType)
//	{
//		return encoder->Initialize(width, height, bps, fps, static_cast<ConfigType>(configType));
//	}
//	extern "C" __declspec(dllexport)  int __cdecl GetDefaultParams(Encoder * encoder, SEncParamExt* params)
//	{
//		return encoder->GetDefaultParams(*params);
//	}
//	
//	extern "C" __declspec(dllexport)  int __cdecl InitializeEncoderBase(Encoder * encoder, SEncParamBase params)
//	{
//		return encoder->Initialize(params);
//	}
//	extern "C" __declspec(dllexport)  int __cdecl InitializeEncoder2(Encoder * encoder, SEncParamExt params)
//	{
//		return encoder->Initialize(params);
//	}
//	extern "C" __declspec(dllexport)  bool __cdecl Encode(Encoder * encoder, GenericImage* img, FrameContainer* fc)
//	{
//		return encoder->Encode(*img, *fc);
//	}
//
//	extern "C" __declspec(dllexport)  bool __cdecl Encode1(Encoder * encoder, byte * yuv, FrameContainer * fc)
//	{
//		return encoder->Encode(yuv, *fc);
//	}
//
//	extern "C" __declspec(dllexport)  int __cdecl ForceIntraFrame(Encoder * encoder)
//	{
//		return encoder->ForceIntraFrame();
//	}
//
//	extern "C" __declspec(dllexport)  void __cdecl SetMaxBitrate(Encoder * encoder, int target)
//	{
//		 encoder->SetMaxBitrate(target);
//	}
//
//	extern "C" __declspec(dllexport)  void __cdecl SetTargetFps(Encoder * encoder, float target)
//	{
//		encoder->SetTargetFps(target);
//	}
//	extern "C" __declspec(dllexport)  void __cdecl SetParallelConverterEnc(Encoder * encoder, int threadCount)
//	{
//		encoder->threadCount= threadCount;
//	}
//	extern "C" __declspec(dllexport)  void __cdecl FreeEncoder(Encoder * encoder)
//	{
//		delete encoder;
//	}
//
//	extern "C" __declspec(dllexport)  int __cdecl SetOptionEncoder(Encoder * encoder, ENCODER_OPTION option, void* value)
//	{
//		return encoder->SetOption(option,value);
//	}
//	extern "C" __declspec(dllexport)  int __cdecl GetOptionEncoder(Encoder * encoder, ENCODER_OPTION option, void* value)
//	{
//		return encoder->GetOption(option, value);
//	}
//	//----------------------Decoder--------------------------------------------------------
//
//	
//	extern "C" __declspec(dllexport)  H264Sharp::Decoder * __cdecl GetDecoder(const wchar_t* dllname)
//	{
//		return new H264Sharp::Decoder(dllname);
//	}
//	extern "C" __declspec(dllexport)  int __cdecl InitializeDecoderDefault(Decoder * decoder)
//	{
//		 return decoder->Initialize();
//	}
//	extern "C" __declspec(dllexport)  int __cdecl InitializeDecoder(Decoder * decoder, SDecodingParam decParam)
//	{
//		return decoder->Initialize(decParam);
//	}
//	extern "C" __declspec(dllexport)  bool __cdecl
//		DecodeAsYUV(Decoder* decoder, unsigned char* frame,int lenght, bool noDelay, DecodingState* state, Yuv420p* decoded)
//	{
//		return decoder->Decode(frame, lenght, noDelay, *state, *decoded);
//	}
//
//
//
//	extern "C" __declspec(dllexport)  bool __cdecl
//		DecodeAsRGB(Decoder * decoder, unsigned char* frame, int lenght, bool noDelay, DecodingState * state, RgbImage * decoded)
//	{
//		return decoder->Decode(frame, lenght, noDelay, *state, *decoded);
//	}
//	
//	extern "C" __declspec(dllexport)  bool __cdecl
//		DecodeAsRGBInto(Decoder * decoder, unsigned char* frame, int lenght, bool noDelay, DecodingState * state, unsigned char * decoded)
//	{
//		return decoder->DecodeExt(frame, lenght, noDelay, *state, decoded);
//	}
//
//	extern "C" __declspec(dllexport)  bool __cdecl
//		DecodeAsRGBInto2(int a)
//	{
//		return true;
//	}
//	
//	extern "C" __declspec(dllexport)  void __cdecl FreeDecoder(Decoder * decoder)
//	{
//		delete decoder;
//	}
//
//	extern "C" __declspec(dllexport)  void __cdecl SetParallelConverterDec(Decoder * decoder, int threadCount)
//	{
//		 decoder->threadCount= threadCount;
//	}
//	extern "C" __declspec(dllexport)  void __cdecl UseSSEYUVConverter(Decoder * decoder, bool isSSE)
//	{
//		decoder->UseSSEConverter(isSSE);
//	}
//	extern "C" __declspec(dllexport)  int __cdecl SetOptionDecoder(Decoder * decoder, DECODER_OPTION option, void* value)
//	{
//		return decoder->SetOption(option, value);
//	}
//	extern "C" __declspec(dllexport)  int __cdecl GetOptionDecoder(Decoder * decoder, DECODER_OPTION option, void* value)
//	{
//		return decoder->GetOption(option, value);
//	}
//
//
//	//-----
//	extern "C" __declspec(dllexport)  void __cdecl YUV420ToRGB( Yuv420p * from, RgbImage * to, int threadCount)
//	{
//		Yuv420P2RGB(to->ImageBytes, from->Y, from->U, from->V, to->Width, to->Height, from->strideY, from->strideU, to->Width * 3, true, threadCount);
//	}
//
//	extern "C" __declspec(dllexport)  void __cdecl RGB2YUV420(RgbImage * from, Yuv420p * to, int threadCount)
//	{
//		RGBtoYUV420Planar(from->ImageBytes, to->Y, from->Width, from->Height, from->Stride, threadCount);
//	}
//	
//	 extern "C" __declspec(dllexport) void __cdecl DownscaleImg(GenericImage * from, GenericImage * to, int multiplier)
//	{
//	    ImageType imtype = from->Type;
//		switch (imtype)
//		{
//			case ImageType::Rgb:
//			case ImageType::Bgr:
//				Downscale24(from->ImageBytes, from->Width, from->Height, from->Stride, to->ImageBytes, multiplier);
//				break;
//
//			default:
//				Downscale32(from->ImageBytes, from->Width, from->Height, from->Stride, to->ImageBytes, multiplier);
//
//			break;
//		}
//		
//	}

#endif


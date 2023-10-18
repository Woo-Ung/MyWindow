#include <fstream>
#include <vector>
#include "ImageExample.h"

#pragma comment (lib,"WindowsCodecs.lib")

//Windows Imaging Component (WIC)
//    BMP
//    GIF
//    ICO
//    JPG
//    PNG
//    TIF
//    DDS
//    Windows Mdeia Photo

   /* 1. 디코더 생성
    2. 프레임 획득
    3. Converter로 데이터를 변환(픽셀포멧 BGRA)
    4. 위 데이터로 IBITMAP 생성*/

//메타(meta)
//    //상위 - 메타버스
//    //트렌드
//
//    ***단어 의미 meta : about***
//        metadata

HRESULT ImageExample::LoadBMP(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
    std::ifstream file;
    file.open(filename, std::ios::binary);

    BITMAPFILEHEADER bfh;
    BITMAPINFOHEADER bih;

    file.read(reinterpret_cast<char*>(&bfh), sizeof(BITMAPFILEHEADER));
    file.read(reinterpret_cast<char*>(&bih), sizeof(BITMAPINFOHEADER));

    if (bfh.bfType != 0x4D42)
    {
        return E_FAIL;
    }
    if (bih.biBitCount != 32)
    {
        return E_FAIL;
    }

    std::vector<char> pixels(bih.biSizeImage); // w * h * bpp

    file.seekg(bfh.bfOffBits);

    int pitch = bih.biWidth * (bih.biBitCount / 8);
    /*file.read(&pixels[0], bih.biSizeImage);*/


    /*for (int y = bih.biHeight - 1; y >= 0; y--)
    {
        file.read(&pixels[y * pitch], pitch);
    }*/

    int index{};
    for (int y = bih.biHeight - 1; y >= 0; y--)
    {
        index = y * pitch;
        for (int x = 0; x < bih.biWidth; x++)
        {   
             char r{}, g{}, b{}, a{};
            file.read(&b, 1);
            file.read(&g, 1);
            file.read(&r, 1);
            file.read(&a, 1);

            if ((unsigned char)r == 30 && (unsigned char)g == 199 && (unsigned char)b == 250)
            {
                r = g = b = a = 0;
            }

            pixels[index++] = b;
            pixels[index++] = g;
            pixels[index++] = r;
            pixels[index++] = a;           
        }
    }

    file.read(&pixels[sizeof(bih.biSizeImage)], bih.biSizeImage);

    file.close();

    HRESULT hr = mspRenderTarget->CreateBitmap(
        D2D1::SizeU(bih.biWidth, bih.biHeight),
        D2D1::BitmapProperties( D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED)),
        ppBitmap
    );
    ThrowIfFailed(hr);    
   
    (*ppBitmap)->CopyFromMemory(nullptr, &pixels[0], pitch);

	return S_OK;
}

HRESULT ImageExample::LoadWIC(LPCWSTR filename, ID2D1Bitmap** ppBitmap)
{
    Microsoft::WRL::ComPtr<IWICBitmapDecoder> decoder;
    HRESULT hr;

    hr = mspWICFactory->CreateDecoderFromFilename(
        filename,
        nullptr,
        GENERIC_READ,
        WICDecodeMetadataCacheOnLoad,
        decoder.GetAddressOf()
    );
    ThrowIfFailed(hr);

    Microsoft::WRL::ComPtr<IWICBitmapFrameDecode> frame;
    hr = decoder->GetFrame(0, frame.GetAddressOf());
    ThrowIfFailed(hr);

    Microsoft::WRL::ComPtr<IWICFormatConverter> converter;
    hr = mspWICFactory->CreateFormatConverter(converter.GetAddressOf());
    ThrowIfFailed(hr);

    ThrowIfFailed(hr);

    hr = converter->Initialize(
        frame.Get(),
        GUID_WICPixelFormat32bppPBGRA,
        WICBitmapDitherTypeNone,
        nullptr,
        0,
        WICBitmapPaletteTypeCustom
    );
    ThrowIfFailed(hr);

    hr = mspRenderTarget->CreateBitmapFromWicBitmap(
        converter.Get(),
        ppBitmap
    );
    ThrowIfFailed(hr);

    return S_OK;
}

HRESULT ImageExample::CreateDeviceResources()
{
	D2DFramework::CreateDeviceResources();

	/*HRESULT hr = LoadBMP(L"Images/32.bmp", mspBitmap.ReleaseAndGetAddressOf());
    ThrowIfFailed(hr);*/ //bmp파일

    HRESULT hr = LoadWIC(L"Images/32.bmp", mspBitmap.ReleaseAndGetAddressOf());
    ThrowIfFailed(hr);

	return S_OK;
}

HRESULT ImageExample::Initialize(HINSTANCE hInstance, LPCWSTR title, UINT w, UINT h)
{
    HRESULT hr = CoInitialize(nullptr);
    ThrowIfFailed(hr);

    hr = CoCreateInstance(
        CLSID_WICImagingFactory,
        nullptr,
        CLSCTX_INPROC_SERVER,
        IID_PPV_ARGS(mspWICFactory.GetAddressOf())
    );
    ThrowIfFailed(hr);

    D2DFramework::Initialize(hInstance, title, w, h);

    return S_OK;
}

void ImageExample::Render()
{
    mspRenderTarget->BeginDraw();
    mspRenderTarget->Clear(D2D1::ColorF(0.0f, 0.2f, 0.4f, 1.0f));

    mspRenderTarget->DrawBitmap(mspBitmap.Get());

    HRESULT hr = mspRenderTarget->EndDraw();

    if (hr == D2DERR_RECREATE_TARGET)
    {
        CreateDeviceResources();
    }
}

void ImageExample::Release()
{
    D2DFramework::Release();

    mspBitmap.Reset();
    mspWICFactory.Reset();

    CoUninitialize();
}

#pragma once

#include "../Gameinfo.h"
#include "Shader.h"

class CShaderManager
{
	DECLARE_SINGLETONE(CShaderManager);

private:
	// 쉐이터들 저장하는 자료구조
	unordered_map<string, CSharedPtr<CShader>> mShaderMap;

	// 상수버퍼 저장하는 자료구조
	unordered_map<string, CSharedPtr<class CConstantBuffer>>mCBufferMap;

public:
	//쉐이더 클래스 생성 해주기
	template <typename T>
	bool CreateShader(const std::string& Name)
	{
		CShader* Shader = FindShader(Name);

		if (Shader)
		{
			return true;
		}

		Shader = new T;

		if (!Shader->Init())
		{
			SAFE_DELETE(Shader);
			return false;
		}

		mShaderMap.insert(std::make_pair(Name, Shader));
		return true;
	}

	class CShader* FindShader(const string& Name);
	void ReleaseShader(const string& Name);
public:
	bool CreateContantBuffer(const string& Name, int Size, int Register, int ShaderBufferType);
	class CConstantBuffer* FindCBuffer(const string& Name);
	void ReleaseCBuffer(const string& Name);

public:
	bool Init();

};


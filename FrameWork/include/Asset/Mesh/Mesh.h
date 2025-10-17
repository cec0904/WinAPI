#pragma once
#include "../../GameInfo.h"
#include "../Asset.h"
/*
	메쉬는
	정점(버텍스) 와 인덱스(정점을 어떻게 연결 할 것인지) 버퍼들을 만들고

	정면 부분 -> LED 부분
	안보여지는 후면부분 -> CASE 부분
	뒷면이라도 정점은 만들어놔야 한다.
	
	메쉬 타입을 만들어서 이를 공유포인터, 스마트포인터 만들거다



*/
// 시계방향 앞면
// 반시계방향 뒷면
// 컬링한다.

// 용도 : 정점버퍼와 인덱스 버퍼를 관리하기 위해서 슬롯으로 만든다.
struct FMeshSlot
{
	// 인덱스 버퍼 : 여러곳에서 사용할 수 있다.
	FIndexBuffer IndexBuffer;
};

class CMesh abstract : public CAsset
{
public:
	CMesh();
	virtual ~CMesh();

protected:
	// 정점버퍼
	FVertexBuffer mVertexBuffer;
	// 메쉬 슬롯
	vector<FMeshSlot*> mMeshSlot;
	// 삼각형으로 그릴지 선으로 그릴지 점으로 그릴지 선택하는 설정값

	/*
		D3D11_PRIMITIVE_TOPOLOGY  어떠한 도형을 그릴지 정해준다.
		POINTLIST		: 점
		LINELIST		: 선
		LINESTRIP		: 선 연결
		TRIANGLELIST	: 삼각형
		TRIANGLESTRIP	: 삼각형 끼리 연결 해준다. 게임에서는 트레일 같은거 만들 때 사용한다. 궤적 만들 때 사용한다.
	*/
	D3D11_PRIMITIVE_TOPOLOGY mPrimitive;




public:
	bool CreateMesh(void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData = nullptr, int IndexSize = 0, int IndexCound = 0, DXGI_FORMAT Fmt = DXGI_FORMAT_UNKNOWN, D3D11_USAGE IndexUsage = D3D11_USAGE_DEFAULT);


public:
	bool CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, int Size, int Count, D3D11_USAGE Usage);
};


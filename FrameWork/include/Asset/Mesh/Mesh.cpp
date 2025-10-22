#include "Mesh.h"
#include "../../Device.h"
CMesh::CMesh()
{
}

CMesh::~CMesh()
{

    size_t Size = mMeshSlot.size();

    for (size_t i = 0; i < Size; i++)
    {
        SAFE_DELETE(mMeshSlot[i]);
    }
}

bool CMesh::CreateMesh(void* VertexData, int Size, int Count, D3D11_USAGE VertexUsage, D3D11_PRIMITIVE_TOPOLOGY Primitive, void* IndexData, int IndexSize, int IndexCount, DXGI_FORMAT Fmt, D3D11_USAGE IndexUsage)
{
    mVertexBuffer.Size = Size;
    mVertexBuffer.Count = Count;
    mVertexBuffer.Data = new char[Size * Count];
    memcpy(mVertexBuffer.Data, VertexData, Size * Count);
    // void* 는 역참조가 안된다.
    // 받을 수는 있는데 사용은 안된다.

    // 정점 버퍼 만들기
    if (!CreateBuffer(&mVertexBuffer.Buffer, D3D11_BIND_VERTEX_BUFFER, VertexData, Size, Count, VertexUsage))
    {
        return false;
    }
    mPrimitive = Primitive;

    // 인덱스 버퍼 만들기
    if (IndexData)
    {
        FMeshSlot* Slot = new FMeshSlot;
        Slot->IndexBuffer.Size = IndexSize;
        Slot->IndexBuffer.Count = IndexCount;
        Slot->IndexBuffer.Fmt = Fmt;
        Slot->IndexBuffer.Data = new char[IndexSize * IndexCount];
        memcpy(Slot->IndexBuffer.Data, IndexData, IndexSize * IndexCount);

        if (!CreateBuffer(&Slot->IndexBuffer.Buffer, D3D11_BIND_INDEX_BUFFER, IndexData, IndexCount, IndexSize, IndexUsage))
        {
            SAFE_DELETE(Slot);
            return false;
        }
        mMeshSlot.push_back(Slot);
    }

    return true;
}

bool CMesh::CreateBuffer(ID3D11Buffer** Buffer, D3D11_BIND_FLAG Flag, void* Data, int Size, int Count, D3D11_USAGE Usage)
{
    // DESC
    // 버퍼 사용 설명서 만들어서
    // 설명서 대로 만들어주세요
    // 버퍼 만드는 용도
    D3D11_BUFFER_DESC BufferDesc = {};

    BufferDesc.ByteWidth = Size * Count;

    // D3D11_USAGE 용도
    // GPU 메모리 사용 방법
    // D3D11_USAGE_DEFAULT          : 비디오 메모리에 만들어진 정보를 갱신할 수 있다.
    // D3D11_USAGE_IMMUTABLE        : 생성할 때만 값을 넣을 수 있다.
    // D3D11_USAGE_DYNAMIC          : 비디오 메모리를 사용하는데 그 데이터를 CPU에도 복사본을 하나 더 만들어서 관리한다. 데이터 이동이 너무 많아서 비효율 적이다. 주로 충돌 파티클 같은 거 만들 때 사용한다.CPU가 직접 쓰기 가능하도록 매핑
    // D3D11_USAGE_STAGING          : CPU 에서 읽기 쓰기 하겠다. 
    if (Usage == D3D11_USAGE_DYNAMIC)
    {
        BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    }
    else if (Usage == D3D11_USAGE_STAGING)
    {
        BufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
    }
    BufferDesc.BindFlags = Flag;
    BufferDesc.Usage = Usage;

    // 버퍼 생성
    D3D11_SUBRESOURCE_DATA BufferData = {};
    BufferData.pSysMem = Data;

    if (FAILED(CDevice::GetInst()->GetDevice()->CreateBuffer(&BufferDesc, &BufferData, Buffer)))
    {
        return false;
    }


    return true;
}

void CMesh::Render()
{

    // 그려줄 도형 타입을 지정해준다. 
    CDevice::GetInst()->GetContext()->IASetPrimitiveTopology(mPrimitive);

    //버텍스 버퍼 셋팅 해준다. 
    UINT stride = mVertexBuffer.Size;
    UINT Offset = 0;
    CDevice::GetInst()->GetContext()->IASetVertexBuffers(0, 1, &mVertexBuffer.Buffer, &stride, &Offset);

    //인덱스 버퍼 유무 판단 
    size_t SlotSize = mMeshSlot.size();

    if (SlotSize > 0)
    {
        for (size_t i = 0; i < SlotSize; ++i)
        {
            CDevice::GetInst()->GetContext()->IASetIndexBuffer(mMeshSlot[i]->IndexBuffer.Buffer, mMeshSlot[i]->IndexBuffer.Fmt, 0);

            //인덱스 참고하여 화면에 도형을 그린다. 
            // 인덱스 갯수, 인덱스 위치, 버텍스의 시작 위치 
            CDevice::GetInst()->GetContext()->DrawIndexed(mMeshSlot[i]->IndexBuffer.Count, 0, 0);
        }
    }
    else
    {
        // 인덱스 버퍼가 없으므로 그냥 그려줄것이다. 
        CDevice::GetInst()->GetContext()->IASetIndexBuffer(nullptr, DXGI_FORMAT_UNKNOWN, 0);
        //정점만 출력해라!
        CDevice::GetInst()->GetContext()->Draw(mVertexBuffer.Count, 0);
    }
}

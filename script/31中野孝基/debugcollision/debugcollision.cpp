//=====================================
//    
//   debugcollision.cpp
//              created by Koki Nakano
//
//=====================================


// <����>
// ����̓f�o�b�O�p�A�����蔻��`��̃\�[�X�R�[�h�ł��B
// �����N���X�Ŕz�z���ꂽrenderer.h���K�v�ɂȂ�܂��B
// static�ϐ��Ȃ̂ŃC���X�^���X�𐶐������Ɋ֐����������Ƃ��ł��܂��B
// Sphere��Cube�͕ʃ��m�Ȃ̂ŗ��������Ă�������
// ����ƁA�t����white.png���A�Z�b�g�t�H���_�ɓ���Ƃ��Ă��������B

//�@���̊֌W���]������Ɨ����������Ȃ�̂ŁA�����Őݒ肵�����C�g��؂��Ă��������B
//�K�C�h��Draw�֐��̒��ɃR�����g�ŏ����Ă��܂��B



#include "main.h"
#include "renderer.h"
#include "debugcollision.h"



//�摜�̃t�@�C���p�X
#define DEBUGCOLLISION_TEXTURE_PASS "asset/texture/white.png"





//Sphere�p
ID3D11ShaderResourceView* DebugSphereCollision::m_Texture;        //�e�N�X�`��
ID3D11Buffer* DebugSphereCollision::m_VertexBuffer[3];            //���_�o�b�t�@

VERTEX_3D DebugSphereCollision::circlevertexZX[CIRCLEVERTEX];
VERTEX_3D DebugSphereCollision::circlevertexXY[CIRCLEVERTEX];
VERTEX_3D DebugSphereCollision::circlevertexYZ[CIRCLEVERTEX];


//Cube�p
ID3D11ShaderResourceView* DebugCubeCollision::m_Texture;          //�e�N�X�`��
ID3D11Buffer*             DebugCubeCollision::m_VertexBuffer;     //���_�o�b�t�@




//-----------------------------------
//  Spehre
//-----------------------------------
void DebugSphereCollision::Init()
{
	float one_deg = 360.0f / CIRCLEVERTEX;     //1���_���Ƃ̊p�x


	//XY�~
	for (int i = 0; i < CIRCLEVERTEX; i++)
	{
		circlevertexXY[i].Position = D3DXVECTOR3(cosf(D3DXToRadian(i * (360.0f / (CIRCLEVERTEX - 1)))), sinf(D3DXToRadian(i * (360.0f / (CIRCLEVERTEX - 1)))), 0.0f);
		circlevertexXY[i].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		circlevertexXY[i].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		circlevertexXY[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	}

	//YZ�~
	for (int i = 0; i < CIRCLEVERTEX; i++)
	{
		circlevertexYZ[i].Position = D3DXVECTOR3(0.0f, cosf(D3DXToRadian(i * (360.0f / (CIRCLEVERTEX - 1)))), sinf(D3DXToRadian(i * (360.0f / (CIRCLEVERTEX - 1)))));
		circlevertexYZ[i].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		circlevertexYZ[i].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		circlevertexYZ[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	}

	//ZX�~
	for (int i = 0; i < CIRCLEVERTEX; i++)
	{
		circlevertexZX[i].Position = D3DXVECTOR3(cosf(D3DXToRadian(i * (360.0f / (CIRCLEVERTEX - 1)))), 0.0f, sinf(D3DXToRadian(i * (360.0f / (CIRCLEVERTEX - 1)))));
		circlevertexZX[i].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		circlevertexZX[i].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		circlevertexZX[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	}



	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));                            //�\���̂̒��g��0�Ŗ��߂�
	bd.Usage     = D3D11_USAGE_DYNAMIC;                     //���_�̏�����ŏ�����������悤�ɂ���
	bd.ByteWidth = sizeof(VERTEX_3D) * CIRCLEVERTEX;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;                //���_�o�b�t�@
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;             //���_�̏�����ŏ�����������悤�ɂ���

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));


	//XY�~
	sd.pSysMem = circlevertexXY;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[0]);     //���_�o�b�t�@��C���f�b�N�X�o�b�t�@�Ȃ�

	//YX�~
	sd.pSysMem = circlevertexYZ;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[1]);     //���_�o�b�t�@��C���f�b�N�X�o�b�t�@�Ȃ�

	//ZX�~
	sd.pSysMem = circlevertexZX;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer[2]);     //���_�o�b�t�@��C���f�b�N�X�o�b�t�@�Ȃ�
	
																			

	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		DEBUGCOLLISION_TEXTURE_PASS,
		NULL,
		NULL,
		&m_Texture,
		NULL);

	//�ǂݍ��݊m�F
	assert(m_Texture);
}



void DebugSphereCollision::Uninit()
{
	m_VertexBuffer[0]->Release();
	m_VertexBuffer[1]->Release();
	m_VertexBuffer[2]->Release();

	m_Texture->Release();
}



void DebugSphereCollision::Draw(D3DXVECTOR3 position, D3DXVECTOR3 rotation, float radius, D3DXCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	////���C�g������
	//LIGHT light;
	//light.Enable = false;
	//light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);  //����
	//D3DXVec4Normalize(&light.Direction, &light.Direction);   //�x�N�g����1�ɂ���
	//light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);       //����
	//light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);       //���ڌ�
	//CRenderer::SetLight(light);


	//�}�g���N�X�ݒ�
	D3DXMATRIX mtxW, mtxT, mtxS, mtxR;
	D3DXMatrixScaling(&mtxS, radius, radius, radius);
	D3DXMatrixRotationYawPitchRoll(&mtxR, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&mtxT, position.x, position.y, position.z);
	mtxW = mtxS * mtxR * mtxT;
	CRenderer::SetWorldMatrix(&mtxW);


	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	CRenderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);


	//�~�̕`��
	Draw_XYCircle();
	Draw_YZCircle();
	Draw_ZXCircle();


	////���C�g������
	//light.Enable = true;
	//CRenderer::SetLight(light);
#endif
}




void DebugSphereCollision::Draw(D3DXVECTOR3 position, D3DXQUATERNION quaternion, float radius, D3DXCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	////���C�g������
	//LIGHT light;
	//light.Enable = false;
	//light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);  //����
	//D3DXVec4Normalize(&light.Direction, &light.Direction);   //�x�N�g����1�ɂ���
	//light.Ambient = D3DXCOLOR(0.2f, 0.2f, 0.2f, 0.2f);       //����
	//light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);       //���ڌ�
	//CRenderer::SetLight(light);



	//�}�g���N�X�ݒ�
	D3DXMATRIX mtxW, mtxT, mtxS, mtxR;
	D3DXMatrixScaling(&mtxS, radius, radius, radius);
	D3DXMatrixRotationQuaternion(&mtxR, &quaternion);
	D3DXMatrixTranslation(&mtxT, position.x, position.y, position.z);
	mtxW = mtxS * mtxR * mtxT;

	CRenderer::SetWorldMatrix(&mtxW);



	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	CRenderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP);



	Draw_XYCircle();
	Draw_YZCircle();
	Draw_ZXCircle();


	////���C�g������
	//light.Enable = true;
	//CRenderer::SetLight(light);
#endif
}





void DebugSphereCollision::Draw_XYCircle()
{
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer[0], &stride, &offset);


	
	//�|���S���`��(���_��,)
	CRenderer::GetDeviceContext()->Draw(CIRCLEVERTEX, 0);
}


void DebugSphereCollision::Draw_YZCircle()
{
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer[1], &stride, &offset);



	//�|���S���`��(���_��,)
	CRenderer::GetDeviceContext()->Draw(CIRCLEVERTEX, 0);
}


void DebugSphereCollision::Draw_ZXCircle()
{
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer[2], &stride, &offset);



	//�|���S���`��(���_��,)
	CRenderer::GetDeviceContext()->Draw(CIRCLEVERTEX, 0);
}












void DebugCubeCollision::Init()
{
	VERTEX_3D vertex[24];

	//���W�̐ݒ�
	{
		//��
		vertex[0].Position  = D3DXVECTOR3(-0.5f,  0.5f, -0.5f);
		vertex[1].Position  = D3DXVECTOR3( 0.5f,  0.5f, -0.5f);
		vertex[2].Position  = D3DXVECTOR3(-0.5f,  0.5f,  0.5f);
		vertex[3].Position  = D3DXVECTOR3( 0.5f,  0.5f,  0.5f);
				  		    
		vertex[4].Position  = D3DXVECTOR3(-0.5f,  0.5f, -0.5f);
		vertex[5].Position  = D3DXVECTOR3(-0.5f,  0.5f,  0.5f);
		vertex[6].Position  = D3DXVECTOR3( 0.5f,  0.5f, -0.5f);
		vertex[7].Position  = D3DXVECTOR3( 0.5f,  0.5f,  0.5f);
			
		//��
		vertex[8].Position  = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
		vertex[9].Position  = D3DXVECTOR3( 0.5f, -0.5f, -0.5f);
		vertex[10].Position = D3DXVECTOR3(-0.5f, -0.5f,  0.5f);
		vertex[11].Position = D3DXVECTOR3( 0.5f, -0.5f,  0.5f);

		vertex[12].Position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
		vertex[13].Position = D3DXVECTOR3(-0.5f, -0.5f,  0.5f);
		vertex[14].Position = D3DXVECTOR3( 0.5f, -0.5f, -0.5f);
		vertex[15].Position = D3DXVECTOR3( 0.5f, -0.5f,  0.5f);
				   
		//�c
		vertex[16].Position = D3DXVECTOR3(-0.5f, -0.5f, -0.5f);
		vertex[17].Position = D3DXVECTOR3(-0.5f,  0.5f, -0.5f);
		vertex[18].Position = D3DXVECTOR3(-0.5f, -0.5f,  0.5f);
		vertex[19].Position = D3DXVECTOR3(-0.5f,  0.5f,  0.5f);
				   
		vertex[20].Position = D3DXVECTOR3( 0.5f, -0.5f, -0.5f);
		vertex[21].Position = D3DXVECTOR3( 0.5f,  0.5f, -0.5f);
		vertex[22].Position = D3DXVECTOR3( 0.5f, -0.5f,  0.5f);
		vertex[23].Position = D3DXVECTOR3( 0.5f,  0.5f,  0.5f);
	}

	//���̂ق��̐ݒ�
	for (int i = 0; i < 24; i++)
	{
		vertex[i].Diffuse  = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		vertex[i].Normal   = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
		vertex[i].TexCoord = D3DXVECTOR2(0.0f, 0.0f);
	}



	//���_�o�b�t�@����
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));                            //�\���̂̒��g��0�Ŗ��߂�
	bd.Usage = D3D11_USAGE_DYNAMIC;                     //���_�̏�����ŏ�����������悤�ɂ���
	bd.ByteWidth = sizeof(VERTEX_3D) * 24;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;                //���_�o�b�t�@
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;             //���_�̏�����ŏ�����������悤�ɂ���

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;
	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);     //���_�o�b�t�@��C���f�b�N�X�o�b�t�@�Ȃ�



	//�e�N�X�`���ǂݍ���
	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		DEBUGCOLLISION_TEXTURE_PASS,
		NULL,
		NULL,
		&m_Texture,
		NULL);

	//�ǂݍ��݊m�F
	assert(m_Texture);
}



void DebugCubeCollision::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
}



void DebugCubeCollision::Draw(D3DXVECTOR3 position, D3DXVECTOR3 rotation, D3DXVECTOR3 radius, D3DXCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	//�}�g���N�X�ݒ�
	D3DXMATRIX mtxW, mtxT, mtxS, mtxR;
	D3DXMatrixScaling(&mtxS, radius.x, radius.y, radius.z);
	D3DXMatrixRotationYawPitchRoll(&mtxR, rotation.y, rotation.x, rotation.z);
	D3DXMatrixTranslation(&mtxT, position.x, position.y, position.z);
	mtxW = mtxS * mtxR * mtxT;

	CRenderer::SetWorldMatrix(&mtxW);



	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	CRenderer::SetMaterial(material);

	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);


	//�|���S���`��(���_��,)
	CRenderer::GetDeviceContext()->Draw(CIRCLEVERTEX, 0);
#endif
}



void DebugCubeCollision::Draw(D3DXVECTOR3 position, D3DXQUATERNION quaternion, D3DXVECTOR3 radius, D3DXCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	//���_�o�b�t�@�ݒ�
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);


	//�}�g���N�X�ݒ�
	D3DXMATRIX mtxW, mtxT, mtxS, mtxR;
	D3DXMatrixScaling(&mtxS, radius.x, radius.y, radius.z);
	D3DXMatrixRotationQuaternion(&mtxR, &quaternion);
	D3DXMatrixTranslation(&mtxT, position.x, position.y, position.z);
	mtxW = mtxS * mtxR * mtxT;

	CRenderer::SetWorldMatrix(&mtxW);


	//�}�e���A���ݒ�
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = color;
	CRenderer::SetMaterial(material);


	//�e�N�X�`���ݒ�
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);

	//�v���~�e�B�u�g�|���W�ݒ�
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	//�|���S���`��(���_��,)
	CRenderer::GetDeviceContext()->Draw(24, 0);
#endif
}
#include "WAVE.h"
#include <iostream>

// ID�T�C�Y
#define ID_MAX 4
// �o�C�g�ϊ�
#define BYTE(X) (X) / 8

// �ǂݍ��݃f�[�^�z��̍ő吔
#define DATA_MAX 2

// RIFF�`�����N
struct RIFF {
	//�`�����NID
	unsigned char chunkID[ID_MAX];
	//�`�����N�T�C�Y
	unsigned long chunkSize;
	//�t�H�[�}�b�g�^�C�v
	unsigned char chunkFormatType[ID_MAX];
};

// FMT�`�����N
struct FMT {
	//�`�����NID
	unsigned char chunkID[ID_MAX];
	//�`�����N�T�C�Y
	unsigned long chunkSize;
	//�t�H�[�}�b�g�^�C�v
	unsigned short waveFormatType;
	//�t�H�[�}�b�g�`�����l��
	unsigned short formatChannel;
	//�T���v�����O���g��
	unsigned long samplesPerSec;
	//�r�b�g���[�g
	unsigned long bytesPerSec;
	//�u���b�N�T�C�Y
	unsigned short blockSize;
	//�ʎq���r�b�g��
	unsigned short bitsPerSample;
};

// DATA�`�����N
struct DATA {
	//�`�����NID
	std::string chunkID;
	//�`�����N�T�C�Y
	unsigned long chunkSize;
};

// �R���X�g���N�^
WAVE::WAVE() :
	file(nullptr), offset(0), index(0), read(0), readMax(0), start(false), end(false), loop(false)
{
	format = {};
	data.clear();
	data.resize(DATA_MAX);
}

// �f�X�g���N�^
WAVE::~WAVE()
{
	end = true;
	if (file != nullptr)
	{
		fclose(file);
		file = nullptr;
	}
}

// �����m�F
int WAVE::CheckChar(unsigned char * data, int dataSize, const std::string & find)
{
	for (unsigned int i = 0; i < find.size(); ++i)
	{
		for (int d = 0; d < dataSize; ++d)
		{
			if (data[d] == find[i])
			{
				break;
			}
			else
			{
				//�����m�F���s
				if (d >= dataSize - 1)
				{
					return -1;
				}
			}
		}
	}

	return 0;
}

// �ǂݍ���
int WAVE::Load(const std::string & fileName)
{
	//�t�@�C���I�[�v��
	if (fopen_s(&file, fileName.c_str(), "rb") != 0)
	{
		return -1;
	}

	//�`�����N�錾
	RIFF riff = {};
	FMT fmt = {};
	DATA data = {};
	offset = 0;

	//RIFF�ǂݍ���
	fread(&riff.chunkID[0], sizeof(riff.chunkID), 1, file);
	offset += sizeof(riff.chunkID);
	if (CheckChar(riff.chunkID, ID_MAX, "RIFF") != 0)
	{
		fclose(file);
		return -1;
	}
	fread(&riff.chunkSize, sizeof(riff.chunkSize), 1, file);
	offset += sizeof(riff.chunkSize);
	fread(&riff.chunkFormatType[0], sizeof(riff.chunkFormatType), 1, file);
	offset += sizeof(riff.chunkFormatType);
	if (CheckChar(riff.chunkFormatType, ID_MAX, "WAVE") != 0)
	{
		fclose(file);
		return -1;
	}

	//FMT�ǂݍ���
	fread(&fmt.chunkID[0], sizeof(fmt.chunkID), 1, file);
	offset += sizeof(fmt.chunkID);
	if (CheckChar(fmt.chunkID, ID_MAX, "fmt ") != 0)
	{
		fclose(file);
		return -1;
	}
	fread(&fmt.chunkSize, sizeof(fmt.chunkSize), 1, file);
	offset += sizeof(fmt.chunkSize);
	fread(&fmt.waveFormatType, sizeof(fmt.waveFormatType), 1, file);
	offset += sizeof(fmt.waveFormatType);
	fread(&fmt.formatChannel, sizeof(fmt.formatChannel), 1, file);
	offset += sizeof(fmt.formatChannel);
	fread(&fmt.samplesPerSec, sizeof(fmt.samplesPerSec), 1, file);
	offset += sizeof(fmt.samplesPerSec);
	fread(&fmt.bytesPerSec, sizeof(fmt.bytesPerSec), 1, file);
	offset += sizeof(fmt.bytesPerSec);
	fread(&fmt.blockSize, sizeof(fmt.blockSize), 1, file);
	offset += sizeof(fmt.blockSize);
	fread(&fmt.bitsPerSample, sizeof(fmt.bitsPerSample), 1, file);
	offset += sizeof(fmt.bitsPerSample);
	//�g������
	std::vector<unsigned char>extended;
	extended.resize(fmt.chunkSize - (sizeof(fmt) - sizeof(fmt.chunkID) - sizeof(fmt.chunkSize)));
	if (extended.size() > 0)
	{
		fread(&extended[0], sizeof(unsigned char) * extended.size(), 1, file);
		offset += sizeof(unsigned char) * extended.size();
	}

	//�_�~�[�錾
	std::string chunkID;
	chunkID.resize(sizeof(unsigned char) * ID_MAX);
	//ID����
	fread(&chunkID[0], sizeof(unsigned char) * ID_MAX, 1, file);
	offset += sizeof(unsigned char) * ID_MAX;

	//DATA�ȊO�̏ꍇ
	while (chunkID != "data")
	{
		//�T�C�Y
		unsigned long size = 0;
		fread(&size, sizeof(size), 1, file);
		offset += sizeof(size);
		//�f�[�^
		std::vector<unsigned char>data;
		data.resize(size);
		fread(&data[0], sizeof(unsigned char) * size, 1, file);
		offset += sizeof(unsigned char) * size;
		//ID
		fread(&chunkID[0], sizeof(unsigned char) * ID_MAX, 1, file);
		offset += sizeof(unsigned char) * ID_MAX;
	}

	//DATA�ǂݍ���
	data.chunkID = chunkID;
	fread(&data.chunkSize, sizeof(data.chunkSize), 1, file);
	offset += sizeof(data.chunkSize);

	//�t�H�[�}�b�g�Z�b�g
	format.wFormatTag      = fmt.waveFormatType;
	format.nChannels       = fmt.formatChannel;
	format.nSamplesPerSec  = fmt.samplesPerSec;
	format.wBitsPerSample  = fmt.bitsPerSample;
	format.nBlockAlign     = format.nChannels * BYTE(format.wBitsPerSample);
	format.nAvgBytesPerSec = format.nSamplesPerSec * format.nBlockAlign;

	//�ǂݍ��ݍő吔�̃Z�b�g
	readMax = data.chunkSize;

	//�z��̃������m��
	for (auto& i : this->data)
	{
		i.resize(format.nAvgBytesPerSec);
	}

	return 0;
}

// �����f�[�^�̓ǂݍ���
int WAVE::Load(void)
{
	if (file == nullptr || end == true)
	{
		if (file != nullptr)
		{
			fclose(file);
		}
		return -1;
	}

	for (unsigned int i = 0; i < format.nAvgBytesPerSec; ++i)
	{
		if (read <= readMax)
		{
			fread(&data[index][i], sizeof(char), 1, file);
			++read;
		}
		else
		{
			data[index][i] = 0;
			if (i + 1 >= format.nAvgBytesPerSec)
			{
				if (loop == false)
				{
					end = true;
					fclose(file);
				}
				else
				{
					read = 0;
					fseek(file, offset, SEEK_CUR);
					printf("���[�v���܂�");
				}
			}
		}
	}

	//�C���f�b�N�X�̍X�V
	++index;
	index %= DATA_MAX;

	return 0;
}

// �t�@�C�������
void WAVE::Close(void)
{
	if (file != nullptr)
	{
		fclose(file);
	}
}

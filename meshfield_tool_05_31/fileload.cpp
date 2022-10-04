//=============================================================================
//
// �t�@�C�����[�h���� [fileload.cpp]
// Author : �H������
//
//=============================================================================
#pragma warning( disable : 4592)
#include <stdio.h>
#include "fileload.h"

namespace file = experimental::filesystem;
using file::recursive_directory_iterator;

//=============================================================================
// �R���X�g���N�^
//=============================================================================
CFileLoad::CFileLoad()
{
	
}

//=============================================================================
// �f�X�g���N�^
//=============================================================================
CFileLoad::~CFileLoad()
{

}

//=============================================================================
// �e�N�X�`���̐���
//=============================================================================
pair<vector<string>, vector<string>> CFileLoad::Load(string load_file)
{
	pair<vector<string>, vector<string>> pas_name_buf;	// �p�X�Ɩ��O�̃o�b�t�@
	vector<string> folder_name;	// �t�H���_�̕ۑ��o�b�t�@
	int count_element = 0;			// �v�f�J�E���g�l

	// �p�X�̃t�@�C������ǂݍ���
	for (const auto &file : recursive_directory_iterator(load_file))
	{
		// �p�X�̕ۑ�
		pas_name_buf.first.push_back(file.path().string());
		pas_name_buf.second.push_back(file.path().string());

		// �p�X���������Ă���
		if (pas_name_buf.second[count_element].find(load_file) != string::npos)
		{
			// �g���q�����Ă�����
			if (pas_name_buf.second[count_element].find(".") != string::npos)
			{
				// �t�H���_�̖��O�T�C�Y���擾
				int folder_max = folder_name.size();
				for (int folder_count = 0; folder_count < folder_max; folder_count++)
				{
					// ���O��ۑ����鏊�Ƀp�X���������Ă�����
					if (pas_name_buf.second[count_element].find(folder_name[folder_count]) != string::npos)
					{
						// �t�H���_�̖��O�̃T�C�Y���擾
						int name_size = folder_name[folder_count].size();
						for (int count_erase = 0; count_erase < name_size + 1; count_erase++)
						{
							// ���O�������c��
							pas_name_buf.second[count_element].erase(pas_name_buf.second[count_element].begin());
						}
					}
				}
				count_element++;
			}
			// �g���q���t���Ă��Ȃ�(�t�H���_�Ȃ̂ŏ���)
			else
			{
				folder_name.push_back(pas_name_buf.second[count_element]);
				pas_name_buf.second.erase(pas_name_buf.second.begin() + count_element);
				pas_name_buf.first.erase(pas_name_buf.first.begin() + count_element);
			}
		}
	}

	return pas_name_buf;
}
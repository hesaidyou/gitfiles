#pragma once

#pragma warning(disable:4996)
#include<cassert>
#include<Windows.h>
#include<string>
#include<iostream>
#include"Huffman.hpp"
typedef long long type;
struct weight    //Ȩֵ��Ӧ�ð����ַ����ֵĴ����Լ���Ӧ���ַ���Huffman����
{
	unsigned char _ch;
	type _count;
	string _code;

	weight(type count = 0)
		: _ch(0)
		,_count(count)
		, _code("")
	{}
	weight operator+(const weight& w)
	{
		type tmp = _count + w._count;
		return weight(tmp);
	}
	bool operator<(const weight& w)
	{
		return _count < w._count;
	}
	bool operator!=(const weight& w)
	{
		return !(_count == w._count);
	}

};

class HuffmanPress
{
public:
	HuffmanPress()
	{
		for (int i = 0; i < 256; i++)
		{
			_infos[i]._ch = (unsigned char)i;
		}
	}

	bool FilePress(const char* filename)
	{
		//ͳ�Ƴ�ÿ���ַ����ֵĴ�����
		FILE* fOut = fopen(filename, "rb");   
		assert(fOut);
		int ch = fgetc(fOut);
		type charcount = 0;  //ͳ�Ƴ��ַ����ֵ��ܴ���
		while (ch != EOF)
		{
			if (feof(fOut))
				break;
			_infos[ch]._count++;
			ch = fgetc(fOut);
			charcount++;
		}
		weight invalid(0);
		HuffmanTree<weight> hf(_infos, 256,invalid);    //�õõ���Ȩ�����鹹��һ��Huffman��
		HuffmanTreeNode<weight>* root = hf.GetRoot();
		//�õ�Huffman����
		string code;
		_GetCodeR(root, code);
		//��ʼѹ��,����ѹ������ļ�
		string CompressFilename = filename;
		CompressFilename += ".huffman";
		FILE* fIn = fopen(CompressFilename.c_str(), "wb");
		assert(fIn);
		//ͳ�������ʹ���ļ�ָ��ָ�������������Ҫʹָ��ָ���ļ�ͷ
		fseek(fOut, 0, SEEK_SET);
		//��ѹ���ļ���д��Huffman����
		int pos = 0;
		char value = 0;
		int ch1 = fgetc(fOut);
		while (ch1 != EOF)
		{
			if (feof(fOut))
				break;
			string& code = _infos[ch1]._code;
			for (size_t i = 0; i < code.size(); i++)
			{
				value <<= 1;
				if (code[i] == '1')  //�õ������Ƶ�1
				{
					value |= 1;
				}
				if (++pos == 8)   //��8λд���ļ�
				{
					fputc(value, fIn);
					value = 0;
					pos = 0;
				}
			}
			
			ch1 = fgetc(fOut);
		}
		if (pos)    //���ı��벻����һ���ֽ�
		{
			value =value<<(8 - pos);
			fputc(value, fIn);
		}
		//���ַ����ַ����ֵĴ���д�������ļ����ļ���ѹʱ���õ�
		string ConfigFilename = filename;
		ConfigFilename += ".config";
		FILE* fConfig = fopen(ConfigFilename.c_str(), "wb");
		assert(fConfig);
		char countStr[20];  //�ַ����ֵĴ���
		//�Ȱ������ַ����ֵ��ܴ���д�������ļ���Ϊ��ֹ����int��Χ��charcountʹ�õ���long long ����Ҫ������д��
		itoa(charcount >> 32, countStr, 10);  //ת����λ
		fputs(countStr, fConfig);  //д��
		fputc('\n', fConfig);
		itoa(charcount & 0Xffffffff, countStr, 10); //ת����λ
		fputs(countStr, fConfig);  //д��
		fputc('\n', fConfig);
		for (int i = 0; i < 256; i++)
		{
			string put;
			if (_infos[i]!=invalid)
			{
				fputc(_infos[i]._ch,fConfig);//�����Ȱ�ch�Ž�ȥ�������ch��Ϊstring���ַ����ת��ΪC���ַ����ᵼ��'\0'û�д���
				put.push_back(',');
				itoa(_infos[i]._count, countStr, 10);
				put += countStr;
				fputs(put.c_str(), fConfig);
				fputc('\n', fConfig);
			}
		}
		fclose(fOut);
		fclose(fIn);
		fclose(fConfig);
		return true;
	}
	bool FileUncompress(char* filename)  //���������ѹ���ļ���
	{
		//1.��ȡ�����ļ�
		string ConfigFilename = filename;
		int count = ConfigFilename.rfind('.');
		ConfigFilename = ConfigFilename.substr(0, count);
		string UnCompressname = ConfigFilename + ".unpress"; 
		FILE* fUnCompress = fopen(UnCompressname.c_str(), "wb"); //������ѹ���ļ�
		ConfigFilename += ".config";
		FILE* fconfig = fopen(ConfigFilename.c_str(),"rb");
		assert(fconfig);
		assert(fUnCompress);
		FILE* fpress = fopen(filename, "rb");  //��ѹ���õ��ļ�
		assert(fpress);

		type charcount = 0; //�ȶ����ַ����ֵ��ܴ���
		string line;
		_ReadLine(fconfig,line);
		charcount = atoi(line.c_str());
		charcount <<= 32;   
		line.clear();
		_ReadLine(fconfig, line);
		charcount += atoi(line.c_str());
		line.clear();
		while (_ReadLine(fconfig,line))  //�ļ�����ʱfeof�᷵��0
		{
			if (!line.empty())
			{
				char ch = line[0];
				_infos[(unsigned char)ch]._count = atoi(line.substr(2).c_str());
				line.clear();
			}
			else  //������һ�����У���Ӧ���ַ�Ϊ���з�
			{
				line += '\n';
			}
		}
		//2.�ٴι���Huffman��
		weight invalid(0);
		HuffmanTree<weight> hf(_infos, 256, invalid);    //�õõ���Ȩ�����鹹��һ��Huffman��
		HuffmanTreeNode<weight>* root = hf.GetRoot();
		HuffmanTreeNode<weight>* cur = root;
		char ch = fgetc(fpress);
		int pos = 8;
		while (1)
		{
			--pos;
			if ((ch >> pos) & 1)
			{
				cur = cur->_right;
			}
			else
			{
				cur = cur->_left;
			}

			if (cur->_left == NULL&&cur->_right == NULL)
			{
				fputc(cur->_weight._ch, fUnCompress);
				cur = root;   //�ٴδӸ��ڵ����
				charcount--;
			}
			if (pos == 0)
			{
				ch = fgetc(fpress);
				pos = 8;
			}
			if (charcount == 0)  //����ȡѹ��ʱΪ�˴չ�һ���ֽڶ��ӽ�ȥ�ı���λ
				break;   
		}

		fclose(fconfig);
		fclose(fpress);
		fclose(fUnCompress);
		return true;
	}

protected:
	bool _ReadLine(FILE* filename,string& line)
	{
		assert(filename);
		if (feof(filename))
			return false;
		unsigned char ch = fgetc(filename);

		while (ch != '\n')
		{
			line += ch;
			ch = fgetc(filename);

			if (feof(filename))
				//break;
				return false;
		}
		return true;
	}

	void _GetCodeR(HuffmanTreeNode<weight>* root, string code)
	{
		if (NULL == root)
			return;
		if (root->_left == NULL&& root->_right == NULL)
		{
			_infos[root->_weight._ch]._code = code;
		
		}
		_GetCodeR(root->_left, code + '0');
		_GetCodeR(root->_right, code + '1');

	}
private:
	weight _infos[256];
};

void TestCompress()
{
	HuffmanPress hft;
	int begin = GetTickCount();
//	hft.FilePress("test1.txt");
	//hft.FilePress("git.txt");
//	hft.FilePress("1.jpg");
//	hft.FilePress("8.pdf");
	//hft.FilePress("Input.BIG");
	hft.FilePress("listen.mp3");
	int end = GetTickCount();
	cout << end-begin << endl;
}

void TestUnCompress()
{
	HuffmanPress hf;
	int begin = GetTickCount();
//	hf.FileUncompress("test1.txt.huffman");
//	hf.FileUncompress("1.jpg.huffman");
//	hf.FileUncompress("git.txt.huffman");
//	hf.FileUncompress("8.pdf.huffman");
	//hf.FileUncompress("Input.BIG.huffman");
	hf.FileUncompress("listen.mp3.huffman");
	int end = GetTickCount();
	cout << end - begin << endl;
}
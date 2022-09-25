#include<iostream>
#include<string>
using namespace std;
int* find_next(string p)
{
	int m = p.length();
	int* next = new int[m];
	int i = 0;//��Ӧ�������next������±�.
	int k = -1;//���������next[i]��ֵ��������Ϊ-1Ҳ�ܺ���.
	next[0] = -1;
	while (i < m - 1)
	{
		while (k >= 0 && p[i] != p[k])//���롰�ݹ顱���ֱ��p[i]==p[k].
		{
			k = next[k];
		}
		i++; k++;
		if (p[i] == p[k])
			next[i] = next[k];//�Ż������������ƥ������������.
		else
			next[i] = k;
	}
	return next;
}
int KMP_string_match(string p, string t, int* next)
{
	int m = p.length(), n = t.length();
	if (m > n)
		return -1;
	int i = 0, j = 0;
	while (i < m && j < n)
	{
		if (i == -1 || p[i] == t[j])//����i=-1�������һ��ʼnext��-1.
		{
			i++; j++;
		}
		else
			i = next[i];
	}
	if (i >= m)
		return j - m;//���ش�0��ʼ�������±�λ��.
	else
		return -1;

}
int main()
{
	string pattern, text;
	cin >> text >> pattern;
	int* next = find_next(pattern);
	int index = KMP_string_match(pattern, text, next);
	if (index == -1)	
		cout << "CANNOT MATCH!" << endl;
	else
	{
		for (int i = 0; i < index; i++)
			cout << '-';
		cout << "^";
		for (int i = 0; i < text.length() - index - 1; i++)
			cout << "-";
		cout << endl;
		cout << index << endl;
	}
}
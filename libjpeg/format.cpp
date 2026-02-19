/*
**	swf2apt
**	Copyright 2025 Jonathan Wilson
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);

extern "C" char* FormatDouble(int p, double d) {
	char* str = new char[64];
	sprintf(str, "%.*f", p, d);
	return str;
}

extern "C" char* FormatDoubleZeroes(int p, double d) {
	char* str = new char[64];
	int size = sprintf(str, "%.*f", p, d);

	for (int i = size - 1, end = size; i >= 0; i--) {
		if (str[i] == '0') {
			if (end == i + 1) {
				end = i;
			}
		}
		else if (str[i] == '.') {
			if (end == i + 1) {
				end = i;
			}
			str[end] = '\0';
			break;
		}
	}

	return str;
}

extern "C" char* FormatDoubleG(int p, double d) {
	char* str = new char[64];
	sprintf(str, "%.*g", p, d);
	return str;
}

extern "C" void FreeFormattedString(char* str)
{
	delete[] str;
}

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

#include <string.h>
#include <stddef.h>
#include <vector>

extern "C" {
#include "jpeglib.h"
};

struct JpegOutput
{
	unsigned int output_width;
	unsigned int output_height;
	int output_components;
	unsigned char* outbuffer;
	int outsize;
};

extern "C" JpegOutput* DecodeJpeg(unsigned char* buffer, int size)
{
	jpeg_decompress_struct cinfo;
	jpeg_error_mgr jerr;
	cinfo.err = jpeg_std_error(&jerr);
	jpeg_create_decompress(&cinfo);
	jpeg_mem_src(&cinfo, buffer, size);
	jpeg_read_header(&cinfo, TRUE);
	jpeg_start_decompress(&cinfo);
	int row_stride = cinfo.output_width * cinfo.output_components;
	JSAMPLE* out = new JSAMPLE[row_stride * cinfo.output_height];
	JSAMPLE* outputptr = out;
	JSAMPARRAY jpegbuffer = (*cinfo.mem->alloc_sarray)((j_common_ptr)&cinfo, JPOOL_IMAGE, row_stride, 1);

	while (cinfo.output_scanline < cinfo.output_height)
	{
		jpeg_read_scanlines(&cinfo, jpegbuffer, 1);
		memcpy(outputptr, jpegbuffer[0], row_stride);
		outputptr += row_stride;
	}

	JpegOutput* outp = new JpegOutput;
	outp->output_width = cinfo.output_width;
	outp->output_height = cinfo.output_height;
	outp->output_components = cinfo.output_components;
	outp->outbuffer = out;
	outp->outsize = row_stride * cinfo.output_height;
	jpeg_finish_decompress(&cinfo);
	jpeg_destroy_decompress(&cinfo);
	return outp;
}

extern "C" void FreeJpeg(JpegOutput* output)
{
	delete[] output->outbuffer;
	delete output;
}

/*
 *  Portions taken from Perl 5.8.9
 *
 *	Copyright (C) 1991, 1992, 1993, 1995, 1996, 1997, 1998, 1999, 2000,
 *	2001, 2002, 2006, 2007, 2008, by Larry Wall and others
 *
 */

#define HASH(hash,str,len) \
	 { \
		const unsigned char *bytes = (const unsigned char *)str; \
		long count = len; \
		unsigned long temphash = 0; \
		while (count--) \
		{ \
			temphash += *bytes++; \
			temphash += (temphash << 10); \
			temphash ^= (temphash >> 6); \
		} \
		temphash += (temphash << 3); \
		temphash ^= (temphash >> 11); \
		hash = (temphash + (temphash << 15)); \
	}

template <class t>
class HashTable
{
private:
	struct HashKey
	{
		unsigned long hash;
		long len;
		char key[1];
	};

	struct HashEntry
	{
		HashEntry* next;
		HashKey* key;
		t val;
	};

public:
	HashTable() : entries(nullptr), fill(0), max(7), keys(0), rehash(false)
	{
		IterInit();
	}

	~HashTable()
	{
		free_entries();
		delete[] entries;
	}

	long IterInit()
	{
		riter = -1;
		eiter = nullptr;
		return keys;
	}

	bool Exists(const char* key)
	{
		HashEntry* entry;
		unsigned long hash;

		if (!entries)
		{
			return false;
		}

		long klen = strlen(key);
		HASH(hash, key, klen);

		entry = entries[hash & max];

		for (; entry; entry = entry->next)
		{
			if (!entry->key)
			{
				continue;
			}

			if (entry->key->hash != hash)
			{
				continue;
			}

			if (entry->key->len != klen)
			{
				continue;
			}

			if (memcmp(entry->key->key, key, klen))
			{
				continue;
			}

			return true;
		}

		return false;
	}

	t& operator[](const char* key)
	{
		HashEntry* entry;
		HashEntry** oentry;
		unsigned long hash;

		if (!entries)
		{
			entries = new HashEntry * [max + 1];
			memset(entries, 0, (max + 1) * 4);
		}

		long klen = strlen(key);
		HASH(hash, key, klen);

		entry = entries[hash & max];

		for (; entry; entry = entry->next)
		{
			if (!entry->key)
			{
				continue;
			}

			if (entry->key->hash != hash)
			{
				continue;
			}

			if (entry->key->len != klen)
			{
				continue;
			}

			if (memcmp(entry->key->key, key, klen))
			{
				continue;
			}

			return entry->val;
		}

		oentry = &entries[hash & max];
		entry = new HashEntry;

		entry->key = save_flags(key, klen, hash);

		if constexpr (std::is_pointer<t>::value)
		{
			entry->val = nullptr;
		}
		else
		{
			entry->val.clear();
		}

		entry->next = *oentry;
		*oentry = entry;
		const HashEntry* counter = entry->next;
		keys++;

		if (!counter)
		{
			fill++;
		}
		else if (keys > max)
		{
			split();
		}
		else
		{
			unsigned long n_links = 1;

			while ((counter = counter->next))
			{
				n_links++;
			}

			if (n_links > 14)
			{
				split();
			}
		}

		return entry->val;
	}

	HashEntry* IterNext()
	{
		HashEntry* entry;
		HashEntry* oldentry;

		oldentry = entry = eiter;

		if (!entries)
		{
			return nullptr;
		}

		if (entry)
		{
			entry = entry->next;
		}

		while (!entry)
		{
			riter++;

			if (riter > max)
			{
				riter = -1;
				break;
			}

			entry = entries[riter];
		}

		eiter = entry;
		return entry;
	}

	HashEntry* Iter()
	{
		return eiter;
	}

private:
	HashEntry** entries;
	long fill;
	long max;
	long keys;
	long riter;
	HashEntry* eiter;
	bool rehash;

	void split()
	{
		const long oldsize = max + 1;
		long newsize = oldsize * 2;
		int longest_chain = 0;
		HashEntry** a = new HashEntry * [newsize];

		memcpy(a, entries, oldsize * 4);
		delete[] entries;

		memset(&a[oldsize], 0, (newsize - oldsize) * 4);
		max = --newsize;
		entries = a;
		HashEntry** aep = a;

		for (long i = 0; i < oldsize; i++, aep++)
		{
			int left_length = 0;
			int right_length = 0;
			HashEntry* entry;
			HashEntry** oentry;

			if (!*aep)
			{
				continue;
			}

			HashEntry** bep = aep + oldsize;

			for (oentry = aep, entry = *aep; entry; entry = *oentry)
			{
				if ((entry->key->hash & newsize) != (unsigned long)i)
				{
					*oentry = entry->next;
					entry->next = *bep;

					if (!*bep)
					{
						fill++;
					}

					*bep = entry;
					right_length++;
					continue;
				}
				else
				{
					oentry = &entry->next;
					left_length++;
				}
			}

			if (!*aep)
			{
				fill--;
			}

			if (left_length > longest_chain)
			{
				longest_chain = left_length;
			}

			if (right_length > longest_chain)
			{
				longest_chain = right_length;
			}
		}

		if (longest_chain <= 14 || rehash)
		{
			return;
		}

		++newsize;
		a = new HashEntry * [newsize];
		memset(a, 0, newsize * 4);

		fill = 0;
		rehash = true;

		aep = entries;

		for (long i = 0; i < newsize; i++, aep++)
		{
			HashEntry* entry = *aep;

			while (entry)
			{
				HashEntry* const next = entry->next;
				unsigned long hash;
				HashEntry** bep;

				HASH(hash, entry->key->key, entry->key->len);
				entry->key->hash = hash;

				bep = a + (hash & max);

				if (!*bep)
				{
					fill++;
				}

				entry->next = *bep;
				*bep = entry;

				entry = next;
			}
		}

		delete[] entries;
		entries = a;
	}

	HashKey* save_flags(const char* str, long len, unsigned long hash)
	{
		char* k = new char[offsetof(HashKey, key[0]) + len + 1];
		HashKey* hek = (HashKey*)k;
		memcpy(hek->key, str, len);
		hek->key[len] = 0;
		hek->len = len;
		hek->hash = hash;
		return hek;
	}

	void free_entry(HashEntry* entry)
	{
		if (!entry)
		{
			return;
		}
		if constexpr (std::is_pointer<t>::value)
		{
			delete[] entry->val;
		}
		else
		{
			for (auto it : entry->val)
			{
				delete[] it;
			}
		}
		delete entry->key;
		delete entry;
	}

	void free_entries()
	{
		HashEntry** const orig_array = entries;
		long i;

		if (!orig_array)
		{
			return;
		}

		i = max;
		entries = nullptr;
		fill = 0;
		keys = 0;

		do
		{
			HashEntry* entry = orig_array[i];

			while (entry)
			{
				HashEntry* const oentry = entry;
				entry = entry->next;
				free_entry(oentry);
			}
		} while (--i >= 0);

		entries = orig_array;
		IterInit();
	}
};

extern "C" HashTable<char*>* GetCharHashTable()
{
	return new HashTable<char*>;
}

extern "C" void FreeCharHashTable(HashTable<char*>* table)
{
	delete table;
}

extern "C" void StoreCharEntry(HashTable<char*>* table, char* key, char* value)
{
	(*table)[key] = _strdup(value);
}

extern "C" int ResetCharIterator(HashTable<char*>* table)
{
	return table->IterInit();
}

extern "C" const char* GetCharValue(HashTable<char*>* table)
{
	return table->IterNext()->val;
}

extern "C" HashTable<char*>* CopyCharHashTable(HashTable<char*>* table)
{
	HashTable<char*>* ret = new HashTable<char*>;
	int count = table->IterInit();
	for (int i = 0; i < count; i++)
	{
		auto entry = table->IterNext();
		(*ret)[entry->key->key] = _strdup(entry->val);
	}
	delete table;
	return ret;
}

extern "C" HashTable<std::vector<char*>>* GetVectorHashTable()
{
	return new HashTable<std::vector<char*>>;
}

extern "C" void FreeVectorHashTable(HashTable<std::vector<char*>>* table)
{
	delete table;
}

extern "C" void StoreVectorEntry(HashTable<std::vector<char*>>* table, char* key)
{
	(*table)[key].clear();
}

extern "C" void StoreVectorListEntry(HashTable<std::vector<char*>>* table, char* key, char* value)
{
	(*table)[key].push_back(_strdup(value));
}

extern "C" int ResetVectorIterator(HashTable<std::vector<char*>>* table)
{
	return table->IterInit();
}

extern "C" char* GetVectorKey(HashTable<std::vector<char*>>* table)
{
	return table->IterNext()->key->key;
}

extern "C" std::vector<char*>* GetVectorValue(HashTable<std::vector<char*>>* table)
{
	return &table->Iter()->val;
}

extern "C" unsigned int GetVectorListSize(std::vector<char*>* v)
{
	return v->size();
}

extern "C" const char* GetVectorListEntry(std::vector<char*>* v, int i)
{
	return (*v)[i];
}

extern "C" bool VectorEntryExists(HashTable<std::vector<char*>>* table, char* key)
{
	return table->Exists(key);
}

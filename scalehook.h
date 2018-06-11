/*
	Copyright 2018 (c) RakLabs

	Licensed under the Apache License, Version 2.0 (the "License");
	you may not use this file except in compliance with the License.
	You may obtain a copy of the License at

		http://www.apache.org/licenses/LICENSE-2.0

	Unless required by applicable law or agreed to in writing, software
	distributed under the License is distributed on an "AS IS" BASIS,
	WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
	See the License for the specific language governing permissions and
	limitations under the License.
*/
/*
//	Welcome to scalehook source code.
//	If you want know what's that, then read:
//		scalehook - cross-platform C/C++ hooking library.
//
//	It will be very helpful for you, if you want:
//		* know your security troubles <3
//		* hook any function c:
//		* something else?
//
//	Some features:
//		1.) Support two types.
//		2.) You can use your own opcodes (not only jmp or call).
//		3.) All! I think that's enough, ha-ha!
//
//	Functions:
//		scalehook_unprotect(void *src, size_t size) - Getting access.
//
//		scalehook_create() - Create a hook (returns scalehook structure or nothing).
//		scalehook_destroy() - Destroy a hook. It very important! If you don't want memory leak (no return anything).
//		scalehook_create_fast() - Create a hook (with settings by default) (returns scalehook structure or nothing).
//		scalehook_fast_hook() - Fast hook (returns true/false).
//
//		scalehook_get_original_address() - Get hook original address
//		scalehook_get_opcode() - Get hook opcodes
//		scalehook_get_src() - Get source.
//		scalehook_get_dst() - Get dest.
//		scalehook_is_installed() - Get installing state
//		scalehook_is_unprotected() - Get unprotecting state
//		scalehook_get_size() - Get size
//
//	Structures:
//		scalehook_t - scalehook structure
//
//	Types:
//		Method type. (no opcodes)
//		Call type. (opcodes)
//
//	Definited types:
//		opcode_t (unsigned char).
//		bytes_t (unsigned char *).
//		address_t (unsigned long).
//
//	Opcodes:
//		Definited opcodes: jmp & call
//		Any opcodes
//
//	Supports:
//		Windows/Linux (x32) (other OS didn't tested).
*/
#ifndef SCALEHOOK_H_
#define SCLAEHOOK_H_
#if defined __WIN32__ || defined _WIN32 || defined WIN32
#define scalehook_windows
#elif defined __LINUX__ || defined __linux__ || defined __linux || defined __FreeBSD__ || defined __OpenBSD__
#define scalehook_unix
#include <stddef.h>
#endif
#if !defined scalehook_windows && !defined scalehook_unix
#error "Damn it! I don't know your OS ):"
#endif
#if defined __cplusplus
#define scalehook_cpp
#else
#define scalehook_c
#endif
#ifdef scalehook_cpp
#define scalehook_extern_c extern "C"
#else
#define scalehook_extern_c
#endif
#ifdef scalehook_windows
#define scalehook_call __stdcall
#define scalehook_export scalehook_extern_c
#else
#define scalehook_call
#define scalehook_export scalehook_extern_c
#endif

// --------------------------------------------------

#define scalehook_opcode_jmp 	0xe9 // jmp opcode
#define scalehook_opcode_call 	0xe8 // call opcode
/*
// Also you can use your own opcode.
*/

// --------------------------------------------------

typedef unsigned char opcode_t;
typedef unsigned long address_t;
typedef unsigned char *bytes_t;

// --------------------------------------------------

typedef struct
{
	bytes_t new_bytes; // new bytes
	bytes_t original_bytes; // original bytes
	void *src; // source address
	void *dst; // dest address
	size_t size; // size
	int type; // type
	opcode_t opcode; // opcode
	address_t original_address; // original oddress
	address_t relative_address; // relative oddress
	int installed;
	int unprotected;
} scalehook_t;

// --------------------------------------------------

enum scalehook_types
{
	scalehook_type_method,
	scalehook_type_call
};

// --------------------------------------------------

scalehook_export int scalehook_call scalehook_unprotect(void *src, size_t size);

scalehook_export scalehook_t scalehook_call *scalehook_create(void *src, void *dst, size_t size, opcode_t opcode, int type);
scalehook_export scalehook_t scalehook_call *scalehook_create_fast(void *src, void *dst);
scalehook_export void scalehook_call scalehook_destroy(scalehook_t *scalehook);
scalehook_export int scalehook_call scalehook_fast_hook(void *src, void *dst);

scalehook_export int scalehook_install(scalehook_t *scalehook);
scalehook_export int scalehook_uninstall(scalehook_t *scalehook);

scalehook_export address_t scalehook_call scalehook_get_original_address(scalehook_t *scalehook);
scalehook_export address_t scalehook_call scalehook_get_relative_address(scalehook_t *scalehook);
scalehook_export size_t scalehook_call scalehook_get_size(scalehook_t *scalehook);
scalehook_export opcode_t scalehook_call scalehook_get_opcode(scalehook_t *scalehook);
scalehook_export int scalehook_call scalehook_is_installed(scalehook_t *scalehook);
scalehook_export int scalehook_call scalehook_is_unprotected(scalehook_t *scalehook);
scalehook_export int scalehook_call scalehook_get_type(scalehook_t *scalehook);
scalehook_export void scalehook_call *scalehook_get_src(scalehook_t *scalehook);
scalehook_export void scalehook_call *scalehook_get_dst(scalehook_t *scalehook);
scalehook_export unsigned char scalehook_call *scalehook_get_original_bytes(scalehook_t *scalehook);
scalehook_export unsigned char scalehook_call *scalehook_get_new_bytes(scalehook_t *scalehook);

#endif // SCALEHOOK_H_
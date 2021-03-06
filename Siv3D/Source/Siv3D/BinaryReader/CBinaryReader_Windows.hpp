﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Platform.hpp>
# if defined(SIV3D_TARGET_WINDOWS)

# ifndef NOMINMAX
#	define  NOMINMAX
# endif
# ifndef STRICT
#	define  STRICT
# endif
# ifndef WIN32_LEAN_AND_MEAN
#	define  WIN32_LEAN_AND_MEAN
# endif
# ifndef _WIN32_WINNT
#	define  _WIN32_WINNT _WIN32_WINNT_WIN7
# endif
# ifndef NTDDI_VERSION
#	define  NTDDI_VERSION NTDDI_WIN7
# endif
# include <Windows.h>
# include <Siv3D/String.hpp>
# include <Siv3D/BinaryReader.hpp>

namespace s3d
{
	class BinaryReader::CBinaryReader
	{
	private:

		HANDLE m_handle = INVALID_HANDLE_VALUE;

		int64 m_size = 0;

		FilePath m_fullPath;

		const void* m_pResource = nullptr;

		int64 m_resourcePos = 0;

		bool m_opened = false;

	public:

		CBinaryReader();

		~CBinaryReader();

		bool open(const FilePath& path);

		void close();

		bool isOpened() const noexcept;

		int64 size() const noexcept;

		int64 setPos(int64 pos);

		int64 getPos();

		int64 read(void* buffer, int64 size);

		int64 read(void* buffer, int64 pos, int64 size);

		int64 lookahead(void* buffer, int64 size);

		int64 lookahead(void* buffer, int64 pos, int64 size);

		const FilePath& path() const;
	};
}

# endif

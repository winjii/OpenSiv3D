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

# include "CHTMLWriter.hpp"

namespace s3d
{
	HTMLWriter::CHTMLWriter::CHTMLWriter()
	{

	}

	HTMLWriter::CHTMLWriter::~CHTMLWriter()
	{
		close();
	}

	bool HTMLWriter::CHTMLWriter::open(const FilePath& path, const String& title, const StringView styleSheet)
	{
		if (m_textWriter.isOpened())
		{
			close();
		}

		if (!m_textWriter.open(path))
		{
			return false;
		}

		m_textWriter.writeln(S3DSTR("<!DOCTYPE html>\n<html>\n<head>\n<meta charset=\"UTF-8\" />"));

		writeElementRaw(title.xml_escaped(), S3DSTR("title"));

		writeElementRaw(styleSheet, S3DSTR("style"));

		m_textWriter.writeln(S3DSTR("</head>\n<body>"));

		return true;
	}

	void HTMLWriter::CHTMLWriter::close()
	{
		if (!m_textWriter.isOpened())
		{
			return;
		}

		m_textWriter.writeln(S3DSTR("</body>\n</html>"));

		m_textWriter.close();
	}

	bool HTMLWriter::CHTMLWriter::isOpened() const
	{
		return m_textWriter.isOpened();
	}

	void HTMLWriter::CHTMLWriter::writeRaw(const StringView view)
	{
		if (!m_textWriter.isOpened())
		{
			return;
		}

		m_textWriter.write(view);
	}

	void HTMLWriter::CHTMLWriter::writeElementRaw(const StringView content, const String& tag)
	{
		writeElementRaw(content, tag, tag);
	}

	void HTMLWriter::CHTMLWriter::writeElementRaw(const StringView content, const String& startTag, const String& endTag)
	{
		if (!m_textWriter.isOpened())
		{
			return;
		}

		m_textWriter.write(S3DSTR("<") + startTag + S3DSTR(">"));

		m_textWriter.write(content);

		m_textWriter.write(S3DSTR("</") + endTag + S3DSTR(">\n"));
	}

	void HTMLWriter::CHTMLWriter::writeElementRaw(const StringView content, const String& tag, const Array<std::pair<String, String>>& styles)
	{
		const String startTag =
			styles.map([](const std::pair<String, String>& keyValue) {
			return keyValue.first + S3DSTR(":") + keyValue.second + S3DSTR(";");
		}).join(S3DSTR(" "), tag + S3DSTR(" style=\""), S3DSTR("\""));

		if (content.isEmpty())
		{
			writeRaw(S3DSTR("<") + startTag + S3DSTR(">"));
		}
		else
		{
			writeElementRaw(content, startTag, tag);
		}
	}

	const FilePath& HTMLWriter::CHTMLWriter::path() const
	{
		return m_textWriter.path();
	}
}

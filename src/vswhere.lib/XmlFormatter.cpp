// <copyright file="XmlFormatter.cpp" company="Microsoft Corporation">
// Copyright (C) Microsoft Corporation. All rights reserved.
// Licensed under the MIT license. See LICENSE.txt in the project root for license information.
// </copyright>

#include "stdafx.h"

using namespace std;

void XmlFormatter::StartDocument(_In_ Console& console)
{
    console.WriteLine(L"<?xml version=\"1.0\"?>");

    if (console.get_Logo())
    {
        console.WriteLine(L"<!-- %ls -->", console.get_Version().c_str());
        console.WriteLine(L"<!-- %ls -->", console.get_Copyright().c_str());
    }
}

void XmlFormatter::StartArray(_In_ Console& console)
{
    console.WriteLine(L"%ls<instances>", m_padding.c_str());
    Push();
}

void XmlFormatter::StartObject(_In_ Console& console, _In_opt_ const wstring& name)
{
    if (name.empty())
    {
        m_objects.push(XmlScope(m_padding, L"instance", true));
        m_objects.top().WriteStart(console);
    }
    else
    {
        m_objects.push(XmlScope(m_padding, name));
    }

    Push();
}

void XmlFormatter::WriteProperty(_In_ Console& console, _In_ const wstring& name, _In_ const wstring& value)
{
    m_objects.top().WriteStart(console);
    console.WriteLine(L"%1$ls<%2$ls>%3$ls</%2$ls>", m_padding.c_str(), name.c_str(), value.c_str());
}

void XmlFormatter::EndObject(_In_ Console& console)
{
    Pop();

    m_objects.top().WriteEnd(console);
    m_objects.pop();
}

void XmlFormatter::EndArray(_In_ Console& console)
{
    Pop();
    console.WriteLine(L"%ls</instances>", m_padding.c_str());
}

wstring XmlFormatter::FormatDate(_In_ const FILETIME& value)
{
    return FormatDateISO8601(value);
}

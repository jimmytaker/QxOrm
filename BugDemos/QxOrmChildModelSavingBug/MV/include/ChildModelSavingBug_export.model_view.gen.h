/************************************************************************************************
** File created by QxEntityEditor 1.2.1 (2018/11/28 09:15) : please, do NOT modify this file ! **
************************************************************************************************/

#ifndef _CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT_H_
#define _CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT_H_

#ifdef _MSC_VER
#pragma once
#endif

#include "../../C/include/ChildModelSavingBug_export.gen.h"

#ifdef _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT QX_DLL_EXPORT_HELPER
#else // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT QX_DLL_IMPORT_HELPER
#endif // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG

#ifdef _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define QX_REGISTER_HPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_HPP_EXPORT_DLL
#define QX_REGISTER_CPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_CPP_EXPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_COMPLEX_CLASS_NAME_HPP_EXPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_COMPLEX_CLASS_NAME_CPP_EXPORT_DLL
#else // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define QX_REGISTER_HPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_HPP_IMPORT_DLL
#define QX_REGISTER_CPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_CPP_IMPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_HPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_COMPLEX_CLASS_NAME_HPP_IMPORT_DLL
#define QX_REGISTER_COMPLEX_CLASS_NAME_CPP_CHILDMODELSAVINGBUG_MODEL_VIEW QX_REGISTER_COMPLEX_CLASS_NAME_CPP_IMPORT_DLL
#endif // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG

#ifndef QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_HPP
#ifdef _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_HPP(x) /* Nothing */
#else // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_HPP(x) QX_DLL_EXPORT_TEMPLATE_HPP(class, qx::QxSingleton< x >)
#endif // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#endif // QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_HPP

#ifndef QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_CPP
#ifdef _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_CPP(x) QX_DLL_EXPORT_TEMPLATE_CPP(class, qx::QxSingleton< x >)
#else // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#define QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_CPP(x) /* Nothing */
#endif // _BUILDING_MODEL_VIEW_CHILDMODELSAVINGBUG
#endif // QX_DLL_EXPORT_CHILDMODELSAVINGBUG_MODEL_VIEW_SINGLETON_CPP

#endif // _CHILDMODELSAVINGBUG_MODEL_VIEW_EXPORT_H_

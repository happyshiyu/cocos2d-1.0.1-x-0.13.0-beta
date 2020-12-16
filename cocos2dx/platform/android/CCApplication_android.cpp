#include "CCApplication.h"
#include "jni/JniHelper.h"
#include "CCDirector.h"
#include "CCEGLView.h"
#include "android/jni/SystemInfoJni.h"
#include <android/log.h>
#include <jni.h>

#include <cstring>

#define  LOG_TAG    "CCApplication_android Debug"
#define  LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG,LOG_TAG,__VA_ARGS__)

NS_CC_BEGIN;

// sharedApplication pointer
CCApplication * CCApplication::sm_pSharedApplication = 0;

CCApplication::CCApplication()
{
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCApplication::~CCApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = NULL;
}

int CCApplication::run()
{
        // Initialize instance and cocos2d.
        if (! initInstance() || ! applicationDidFinishLaunching())
        {
                return 0;
        }
	
	return -1;
}

void CCApplication::setAnimationInterval(double interval)
{
	JniMethodInfo methodInfo;
	if (! JniHelper::getStaticMethodInfo(methodInfo, "org/cocos2dx/lib/Cocos2dxRenderer", "setAnimationInterval", 
		"(D)V"))
	{
		CCLOG("%s %d: error to get methodInfo", __FILE__, __LINE__);
	}
	else
	{
		methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID, interval);
	}
}

CCApplication::Orientation CCApplication::setOrientation(Orientation orientation)
{
    return orientation;
}

void CCApplication::statusBarFrame(CCRect * rect)
{
    if (rect)
    {
        // android doesn't have status bar.
        *rect = CCRectMake(0, 0, 0, 0);
    }
}

//////////////////////////////////////////////////////////////////////////
// static member function
//////////////////////////////////////////////////////////////////////////
CCApplication& CCApplication::sharedApplication()
{
    CC_ASSERT(sm_pSharedApplication);
    return *sm_pSharedApplication;
}

ccLanguageType CCApplication::getCurrentLanguage()
{
    const char *pLanguageName = getCurrentLanguageJNI();
    ccLanguageType ret = kLanguageEnglish;
	
	
    if (0 == strcmp("zh", pLanguageName))
    {
        ret = kLanguageChinese;
    }
    else if (0 == strcmp("en", pLanguageName))
    {
        ret = kLanguageEnglish;
    }
    else if (0 == strcmp("fr", pLanguageName))
    {
        ret = kLanguageFrench;
    }
    else if (0 == strcmp("it", pLanguageName))
    {
        ret = kLanguageItalian;
    }
    else if (0 == strcmp("de", pLanguageName))
    {
        ret = kLanguageGerman;
    }
    else if (0 == strcmp("es", pLanguageName))
    {
        ret = kLanguageSpanish;
    }
	else if (0 == strcmp("ru", pLanguageName))
    {
        ret = kLanguageRussian;
    }
	else if (0 == strcmp("ja", pLanguageName))
    {
        ret = kLanguageJanpanese;
    }
	else if (0 == strcmp("pt", pLanguageName))
    {
        ret = kLanguagePortuguese;
    }
	else if (0 == strcmp("ko", pLanguageName))
    {
        ret = kLanguageKorean;
    }
	else if (0 == strcmp("in", pLanguageName))
    {
        ret = kLanguageIndonesian;
    }
	else if (0 == strcmp("th", pLanguageName))
    {
        ret = kLanguageThai;
    }
	else if (0 == strcmp("nl", pLanguageName))
    {
        ret = kLanguageDutch;
    }
	else if (0 == strcmp("fa", pLanguageName))
    {
        ret = kLanguageArab;
    }
	else if (0 == strcmp("pl", pLanguageName))
    {
        ret = kLanguagePolish;
    }
    
    return ret;
}

NS_CC_END;

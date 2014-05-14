/*************************************************************************
	> File Name: noncopyable.h
	> Author: Zhlin
	> Mail:vimquee@gmail.com 
	> Created Time: 2014年05月07日 星期三 21时52分13秒
 ************************************************************************/

#ifndef _NONCOPYABLE_H_
#define _NONCOPYABLE_H_

class noncopyable
{
	protected:
		noncopyable()
		{}
		~noncopyable()
		{}
	private:
		noncopyable(const noncopyable&);
		const noncopyable &operator= (const noncopyable&);
};
#endif



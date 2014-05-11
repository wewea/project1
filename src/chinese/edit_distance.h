#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_
class Query;
class EditDist
{
	friend class Query;
private:
	std::string _key_word;
	int _frequence;
	int _edit_dist;
public:
	EditDist(std::string key_word, int frequence, int edit_dist):_key_word(key_word), _frequence(frequence),
	_edit_dist(edit_dist)
	{}
	friend bool operator<(EditDist a, EditDist b)
	{
		if(a._edit_dist != b._edit_dist )
		{
			return a._edit_dist > b._edit_dist;
		}
		else
		{
			return a._frequence > b._frequence;
		}
	}
};

class EditDist2
{
	friend class Query;
private:
	std::string _key_word;
	int _frequence;
	int _edit_dist;
public:
	EditDist2(std::string key_word, int frequence, int edit_dist):_key_word(key_word), _frequence(frequence),
	_edit_dist(edit_dist)
	{}
	friend bool operator<(EditDist2 a, EditDist2 b)
	{
		if(a._frequence != b._frequence )
		{
			return a._frequence > b._frequence;
		}
		else
		{
			return a._edit_dist > b._edit_dist;
		}
	}
};

/*struct cmp
{
	operator bool()(const node& a, const node& b)
	{
		if(a.edit_dist != b.edit_dist )
		{
			return a.edit_dist < b.edit_dist;
		}
		else
		{
			return a.frequence < b.frequence;
		}
	}
};*/
#endif
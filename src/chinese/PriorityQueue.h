#ifndef _PRIORITYQUEUE_H_
#define _PRIORITYQUEUE_H_
class Query;
class EditDist
{
friend class Query;
private:
	std::string _key_word;
	size_t _frequence;
	size_t _edit_dist;
public:
	EditDist(std::string key_word, size_t frequence, size_t edit_dist):_key_word(key_word), _frequence(frequence),
	_edit_dist(edit_dist)
	{}
	friend bool operator<(EditDist a, EditDist b)
	{
		if(a._edit_dist != b._edit_dist )
		{
			return a._edit_dist > b._edit_dist;//from lesser to greater
		}
		else
		{
			return a._frequence < b._frequence;// from greater to lesser
		}
	}
};

#endif

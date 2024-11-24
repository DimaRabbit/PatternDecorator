#include<iostream>
#include<map>
#include<string>

using namespace std;

class veryHeavyDataBase
{
public:
	virtual string getData(const string& key)const noexcept
	{
		return "Very Big Data string " + key;
	}

};

	class cashProxyDB : public veryHeavyDataBase 
	{
	private:
		veryHeavyDataBase* real_db_;
		map<string, string>casche_;
	public:
		explicit cashProxyDB(veryHeavyDataBase* real_obj) : real_db_(real_obj) {}
		string getData(const string& key)noexcept 
		{
			if (casche_.find(key) == casche_.end()) 
			{
				cout << "Get from real object\n";
				casche_[key] = real_db_->getData(key);
			}
			else 
			{
				cout << "Get from casche\n";
			}
			return casche_.at(key);
		}
	};

	class TestData : public veryHeavyDataBase
	{
	private:
		veryHeavyDataBase* real_db_;
	public:
		explicit TestData(veryHeavyDataBase* real_obj) : real_db_(real_obj) {}
		string getData(const string& key)noexcept
		{
			return "Test_data\n";
		
		}
	};

	class OneShotDB : public veryHeavyDataBase 
	{
	private:
		veryHeavyDataBase* real_db_;
		mutable size_t shots_remaining_;
	public:
		explicit OneShotDB(veryHeavyDataBase* real_obj, size_t shots = 1) : real_db_(real_obj), shots_remaining_(shots) {}
		string getData(const string& key)const noexcept override 
		{
			if (shots_remaining_ > 0) {
				--shots_remaining_;
				return real_db_->getData(key);
			}
			return "Error";
		}
	
	};

	int main() 
	{
		auto real_db = veryHeavyDataBase();

		auto limit_db = OneShotDB(addressof(real_db), 2);
		cout << limit_db.getData("key")<<endl;
		cout << limit_db.getData("key") << endl;
		cout << limit_db.getData("key") << endl;

	
		return 0;
	}


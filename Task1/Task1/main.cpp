#include<iostream>
#include<algorithm>
#include<string>

using namespace std;

class Text 
{
public:
	virtual void render(const string& data) const {
		cout << data;
	}

	virtual ~Text() = default;
};

class DecoratorText : public Text
{
protected:
	Text* text_;
public:
	explicit DecoratorText(Text* text) : text_(text) {}
	virtual ~DecoratorText() {
		delete text_;
	}
};

class Paragraph :public DecoratorText 
{
public:
	explicit Paragraph(Text* text) : DecoratorText(text) {};
	void render(const string& data)const override {
		cout << "<p>";
		text_->render(data);
		cout << "</p>";
	}
};

class Reversed :public DecoratorText 
{
public:
	explicit Reversed(Text* text) : DecoratorText(text) {};
	void render(const string& data)const override {
		string reversed_data = data;
		reverse(reversed_data.begin(), reversed_data.end());
		text_->render(reversed_data);	
	}
};

class Link : public DecoratorText 
{
public:
	explicit Link(Text* text) : DecoratorText(text) {};
	void render(const string& href, const string& data)const {
		cout << "<a href=\"" << href << "\">";
		text_->render(data);
		cout << "</a>";
	}
};

int main() 
{
	auto text_block1 = new Paragraph(new Text());
	text_block1->render("Hello World");
	cout << endl;

	auto text_block2 = new Reversed(new Text());
	text_block2->render("Hello World");
	cout << endl;

	auto text_block3 = new Link(new Text());
	text_block3->render("netology","Hello World");
	cout << endl;

	delete text_block1;
	delete text_block2;
	delete text_block3;

	return 0;
}
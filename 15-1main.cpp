#include <iomanip>
#include <ios>
#include <stdexcept>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include "ptr.h"

using std::istream;
using std::ostream;
using std::back_inserter;
using std::copy;
using std::strlen;
using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Picture;
class Pic_base;
class String_Pic;
class Frame_Pic;
class HCat_Pic;
class VCat_Pic;

class Pic_base {
    friend std::ostream& operator<<(std:: ostream&, const Picture&);
    friend class Frame_Pic;
    friend class HCat_Pic;
    friend class VCat_Pic;
    friend class String_Pic;

    // no public interface(except for destructor)
    typedef std::vector<std::string>::size_type ht_sz;
    typedef std::string::size_type wd_sz;

    // this class is an abstract base class
    virtual wd_sz width() const = 0;
    virtual ht_sz height() const = 0;
    virtual void display(std::ostream&, ht_sz, bool) const = 0;

public:
    virtual ~Pic_base() { }

protected:
    static void pad(std::ostream& os, wd_sz beg, wd_sz end) {
        while (beg != end) {
            os << " ";
            ++beg;
        }
    }
};




class String_Pic: public Pic_base
{
    friend class Picture;
    std::vector<std::string> data;
    String_Pic(const std::vector<std::string>& v): data(v) { }

    ht_sz height() const { return data.size(); }
    wd_sz width() const;
    void display(std:: ostream&, ht_sz, bool) const;
};

Pic_base::wd_sz String_Pic::width() const
{
    Pic_base::wd_sz n = 0;
    for (Pic_base::ht_sz i = 0; i != data.size(); ++i)
        n = std::max(n, data[i].size());
    return n;
}

void String_Pic::display(ostream &os, ht_sz row, bool do_pad) const
{
    wd_sz start = 0;

    // write the row if we're still in range
    if (row < height()) {
        os << data[row];
        start = data[row].size();
    }

    // pad the output if necessary
    if (do_pad)
        pad(os, start, width());

}

class Picture
{
    friend std::ostream& operator<<(std::ostream&, const Picture&);
    friend Picture frame(const Picture&);
    friend Picture hcat(const Picture&, const Picture&);
    friend Picture vcat(const Picture&, const Picture&);

public:
    Picture(const std::vector<std::string>& v):
        p(new String_Pic(v)) { }
private:
    Picture(Pic_base* ptr): p(ptr) { }
    Ptr<Pic_base> p;

};

class VCat_Pic: public Pic_base
{
    friend Picture vcat(const Picture&, const Picture&);
    Ptr<Pic_base> top, bottom;
    VCat_Pic(const Ptr<Pic_base>& t, const Ptr<Pic_base>& b) : top(t), bottom(b) { }

    wd_sz width() const
        { return std::max(top->width(), bottom->width()); }
    ht_sz height() const
        { return top->height() + bottom->height(); }
    void display(std::ostream&, ht_sz, bool) const;
};

void VCat_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
    wd_sz w = 0;
    if (row < top->height()) {
        // we are in the top subpicture
        top->display(os, row, do_pad);
        w = top->width();
    } else if (row < height()) {
        // we are in the bottom subpicture
        bottom->display(os, row - top->height(), do_pad);
        w = bottom->width();
    }
    if (do_pad)
        pad(os, w, width());
}

class HCat_Pic: public Pic_base
{
    friend Picture hcat(const Picture&, const Picture&);
    Ptr<Pic_base> left, right;
    HCat_Pic(const Ptr<Pic_base>& l, const Ptr<Pic_base>& r):
        left (l), right(r) { }

    wd_sz width() const { return left->width() + right->width(); }
    ht_sz height() const
        { return std::max(left->height(), right->height()); }
    void display(std::ostream&, ht_sz, bool) const;
};

void HCat_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
    left->display(os, row, do_pad || row < right->height());
    right->display(os, row, do_pad);
}

class Frame_Pic: public Pic_base
{
    friend Picture frame(const Picture&);
    Ptr<Pic_base> p;
    Frame_Pic(const Ptr<Pic_base>& pic) : p(pic) { }

    wd_sz width() const { return p->width() + 4; }
    ht_sz height() const { return p->height() + 4; }
    void display(std::ostream&, ht_sz, bool) const;
};

void Frame_Pic::display(ostream& os, ht_sz row, bool do_pad) const
{
    if (row >= height()) {

        // out of range
        if (do_pad)
            pad(os, 0 , width());

    } else {
        if (row == 0 || row == height() - 1) {
            // top or bottom row
            os << string(width(), '*');

        } else if (row == 1 || row == height() - 2) {
            // second from top or bottom row
            os << "*";
            pad (os, 1, width() - 1);
            os << "*";
        } else {
            // interior row
            os << "* ";
            p->display(os, row - 2, true);
            os << " *";
        }
    }
}

Picture frame(const Picture& pic)
{
    return new Frame_Pic(pic.p);
}

Picture hcat(const Picture& l, const Picture& r)
{
    return new HCat_Pic(l.p, r.p);
}

Picture vcat(const Picture& t, const Picture& b)
{
    return new VCat_Pic(t.p, b.p);
}

ostream& operator<<(ostream& os, const Picture& picture)
{
    const Pic_base::ht_sz ht = picture.p->height();
    for (Pic_base::ht_sz i = 0; i != ht; ++i) {
        picture.p->display(os, i, false);
        os << endl;
    }
    return os;
}


int main()
{
    vector<string> v;
    v.push_back("*****   ");
    v.push_back("**  **  ");
    v.push_back("****    ");
    v.push_back("**  **  ");
    v.push_back("*****   ");


    Picture p(v);
    Picture q = frame(p);
    Picture r = hcat(p, q);
    Picture s = vcat(q, r);
    cout << frame(hcat(s, vcat(r, q))) << endl;


    return 0;
}

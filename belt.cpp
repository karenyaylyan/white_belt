#include <iostream>
#include <stdexcept>
#include <string>
#include <map>
#include <set>
#include <sstream>
#include <iomanip>

using namespace std;

class Date {
public:
    Date (int new_year, int new_month, int new_day) {
        /*cout << new_year << ' ' << new_month << ' ' << new_day << endl;*/
        if (new_month < 1 || new_month > 12)
            throw logic_error("Month value is invalid: "
                + to_string(new_month)); // month is out of ranges
        else if (new_day < 1 || new_day > 31)
            throw logic_error("Day value is invalid: "
                + to_string(new_day)); // day is out of range
        year = new_year;
        month = new_month;
        day = new_day;
    }
  int GetYear() const {
    return year;
  }
  int GetMonth() const {
    return month;
  }
  int GetDay() const {
    return day;
  }
private:
    int year;
    int month;
    int day;
};


bool operator<(const Date& lhs, const Date& rhs) {
    return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} <
      vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

ostream& operator<< (ostream& stream, const Date& date) {
    stream <<   setw(4) << setfill('0') << date.GetYear() << '-' <<
                setw(2) << setfill('0') << date.GetMonth() << '-' <<
                setw(2) << setfill('0') << date.GetDay();

    return stream;
}

class Database {
public:
  void AddEvent(const Date& date, const string& event) {
    date_to_events[date].insert(event);
  }
  bool DeleteEvent(const Date& date, const string& event) {
    if (date_to_events.count(date) > 0 && date_to_events[date].count(event) > 0)
    {
        cout << "Deleted successfully" << endl;
        return true;
    }
    else
    {
        cout << "Event not found" << endl;
        return false;
    }
  }

  int  DeleteDate(const Date& date) {
    int n = 0;

    if (date_to_events.count(date) > 0)
    {
        n = date_to_events[date].size();
        date_to_events.erase(date);
    }
    cout << "Deleted " << n << " events" << endl;
    return n;
  }

  void Find(const Date& date) const {
  if (date_to_events.count(date) > 0)
  {
    for (const auto& x : date_to_events.at(date))
    {
        cout << x << endl;
    }
  }
}
  
  void Print() const {
    for (const auto& x : date_to_events)
    {
        for (const auto& y: x.second)
        {
            cout << x.first << ' ' << y << endl;
        }
    }
  }
private:
    map<Date, set<string>> date_to_events;

};



/*istream& operator>> (istream& stream, Date& date) {
    int year;
    int month;
    int day;

    char c1;
    char c2;

    if (stream >> year >> c1 >> month >> c2 >> day)
    {
        throw exception("")
    }
    

    date = Date(year, month, day);
}*/

Date ParseDate (const string& s) {
    stringstream stream(s);
    int y;
    int m;
    int d;

    stream >> y;
    if (stream.peek() != '-')
    {
        throw runtime_error("Wrong date format: " + s);
    }
    stream.ignore(1);

    stream >> m;
    if (stream.peek() != '-')
    {
        throw runtime_error("Wrong date format: " + s);
    }
    stream.ignore(1);
    stream >> d;

    Date date = Date(y, m, d);

    return date;


}

int main() {
  Database db;
    
  string command;

  try 
  {
    while (getline(cin, command)) {
        stringstream ss(command);
        string s;
        ss >> s;

        if (s == "Add")
        {
            string dttm;
            ss.ignore(1);
            ss >> dttm;
            Date date = ParseDate(dttm);

            string event;
            ss.ignore(1);
            ss >> event;
        
            db.AddEvent(date, event);
        }
        else if (s == "Del")
        {
            string dttm;
            ss.ignore(1);
            ss >> dttm;
            Date date = ParseDate(dttm);

            string event;
            ss.ignore(1);
            if (ss >> event)
            {
                db.DeleteEvent(date, event);
            }
            else
            {
                db.DeleteDate(date);
            }
        }
        else if (s == "Find")
        {
            string dttm;
            ss.ignore(1);
            ss >> dttm;
            Date date = ParseDate(dttm);
            
            db.Find(date);
        }
        else if (s == "Print")
        {
            db.Print();
        }
        else if (s == "")
        {
            continue;
        }
        else
        {
            cout << "Unknown command: " << command << endl;
        }
    }    
  }
  catch (exception& e)
  {
    cout << e.what() << endl;
  }
      

  return 0;
}

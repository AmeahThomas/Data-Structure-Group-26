#include <iostream>
#include <string>
#include <limits>

using namespace std;

struct Node
{
    string url;
    Node *prev;
    Node *next;
};

class BrowserHistory
{

private:
    Node *head;
    Node *tail;
    Node *current;

public:
    BrowserHistory()
    {
        head = nullptr;
        tail = nullptr;
        current = nullptr;
    }

    ~BrowserHistory()
    {

        Node *temp = head;

        while (temp != nullptr)
        {

            Node *nextNode = temp->next;

            delete temp;

            temp = nextNode;
        }

        cout << "Browsing history memory released successfully!" << endl;
    }

    void visitWebsite(string url)
    {

        if (url.empty())
        {
            cout << "Error: Website address cannot be empty!" << endl;
            return;
        }

        if (current != nullptr)
        {

            Node *temp = current->next;

            while (temp != nullptr)
            {
                Node *nextNode = temp->next;
                delete temp;
                temp = nextNode;
            }

            current->next = nullptr;
            tail = current;
        }

        Node *newNode = new Node;

        newNode->url = url;
        newNode->prev = nullptr;
        newNode->next = nullptr;

        if (head == nullptr)
        {

            head = newNode;
            tail = newNode;
            current = newNode;
        }
        else
        {

            newNode->prev = current;
            current->next = newNode;

            current = newNode;
            tail = newNode;
        }

        cout << "Website visited successfully: " << url << endl;
    }

    void goBack()
    {

        if (current == nullptr || current->prev == nullptr)
        {

            cout << "No previous page available!" << endl;
        }
        else
        {

            current = current->prev;

            cout << "Moved back to: " << current->url << endl;
        }
    }

    void goForward()
    {

        if (current == nullptr || current->next == nullptr)
        {

            cout << "No next page available!" << endl;
        }
        else
        {

            current = current->next;

            cout << "Moved forward to: " << current->url << endl;
        }
    }

    void displayCurrentPage()
    {

        if (current == nullptr)
        {

            cout << "No website is currently open!" << endl;
        }
        else
        {

            cout << "Current Page: " << current->url << endl;
        }
    }

    void displayHistory()
    {

        if (head == nullptr)
        {

            cout << "Browsing history is empty!" << endl;
            return;
        }

        Node *temp = head;

        int count = 1;

        cout << "\n========== BROWSING HISTORY ==========" << endl;

        while (temp != nullptr)
        {

            cout << count << ". " << temp->url;

            if (temp == current)
            {
                cout << "  <-- CURRENT";
            }

            cout << endl;

            temp = temp->next;

            count++;
        }

        cout << "======================================" << endl;
    }

    void searchWebsite(string url)
    {

        Node *temp = head;

        while (temp != nullptr)
        {

            if (temp->url == url)
            {

                cout << "Website found!" << endl;
                cout << "Address: " << temp->url << endl;

                return;
            }

            temp = temp->next;
        }

        cout << "Website not found in browsing history!" << endl;
    }

    void deleteWebsite(string url)
    {

        Node *temp = head;

        while (temp != nullptr && temp->url != url)
        {

            temp = temp->next;
        }

        if (temp == nullptr)
        {

            cout << "Website not found in browsing history!" << endl;
            return;
        }

        if (temp == head)
        {

            head = temp->next;
        }

        if (temp == tail)
        {

            tail = temp->prev;
        }

        if (temp->prev != nullptr)
        {

            temp->prev->next = temp->next;
        }

        if (temp->next != nullptr)
        {

            temp->next->prev = temp->prev;
        }

        if (temp == current)
        {

            if (temp->prev != nullptr)
            {

                current = temp->prev;
            }
            else
            {

                current = temp->next;
            }
        }

        delete temp;

        cout << "Website deleted successfully!" << endl;
    }

    void updateWebsite(string oldUrl, string newUrl)
    {

        Node *temp = head;

        while (temp != nullptr && temp->url != oldUrl)
        {
            temp = temp->next;
        }

        if (temp == nullptr)
        {
            cout << "Website not found in browsing history!" << endl;
            return;
        }

        if (newUrl.empty())
        {
            cout << "Error: New website address cannot be empty!" << endl;
            return;
        }

        temp->url = newUrl;

        cout << "Website updated successfully!" << endl;
    }
};

int main()
{
    BrowserHistory browser;

    int choice;

    cout << "========================================" << endl;
    cout << "        BROWSER HISTORY SIMULATOR" << endl;
    cout << "========================================" << endl;

    while (true)
    {
        cout << "\n1. Visit Website" << endl;
        cout << "2. Go Back" << endl;
        cout << "3. Go Forward" << endl;
        cout << "4. Display Current Page" << endl;
        cout << "5. Display Full History" << endl;
        cout << "6. Search Website" << endl;
        cout << "7. Delete Website" << endl;
        cout << "8. Update Website" << endl;
        cout << "9. Exit" << endl;

        cout << "\nEnter your choice: ";

        if (!(cin >> choice))
        {
            cout << "Invalid input! Please enter a number." << endl;

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1)
        {
            string url;

            cout << "Enter website address: ";

            getline(cin, url);

            browser.visitWebsite(url);
        }

        else if (choice == 2)
        {
            browser.goBack();
        }

        else if (choice == 3)
        {
            browser.goForward();
        }

        else if (choice == 4)
        {
            browser.displayCurrentPage();
        }

        else if (choice == 5)
        {
            browser.displayHistory();
        }
        else if (choice == 6)
        {
            string url;

            cout << "Enter website address to search: ";

            getline(cin, url);

            browser.searchWebsite(url);
        }

        else if (choice == 7)
        {
            string url;

            cout << "Enter website address to delete: ";

            getline(cin, url);

            browser.deleteWebsite(url);
        }

        else if (choice == 8)
        {
            string oldUrl, newUrl;

            cout << "Enter existing website address to update: ";

            getline(cin, oldUrl);

            cout << "Enter new website address: ";

            getline(cin, newUrl);

            browser.updateWebsite(oldUrl, newUrl);
        }

        else if (choice == 9)
        {
            cout << "Exiting Browser History Simulator..." << endl;
            break;
        }

        else
        {
            cout << "Invalid choice! Please try again." << endl;
        }
    }

    return 0;
}
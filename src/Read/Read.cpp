#include <unistd.h>
#include <bits/stdc++.h>

#include "Read.h"

#include <iostream>
#include <memory>

void Read::FirstRead::readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const
{
    std::string buffer(BUFFER_SIZE, '\0');
    defaultRead(queue, info, buffer);

    uint numberOfSpaces = removeSpacesAndTabs(buffer);
    if (numberOfSpaces != 2 && numberOfSpaces != 1)
    {
        WriteError(queue, info, 2);
        return;
    }

    if (buffer.find_first_of(FIRST_WORD) != 0)
    {
        WriteError(queue, info, 3);
        return;
    }

    buffer.erase(buffer.begin(), buffer.begin() + sizeof(FIRST_WORD) / sizeof(char));

    try
    {
        queue.m_mapCreator.get()->atOperateMap(buffer);
    }
    catch (std::exception &e)
    {
        WriteError(queue, info, 6);
    }

    const char *bufferInChar{buffer.c_str()};
    char newBuffer[BUFFER_SIZE];
    strcpy(newBuffer, bufferInChar);

    ThreadPool::FirstWriteCreator firstWriteCreator;
    firstWriteCreator.addToQueue(queue, {std::make_shared<std::string_view>(newBuffer),
                                         info.version, info.sockfd, 0});
}

void Read::SecondRead::readMessage(ThreadPool::Queue &queue, const ThreadPool::readParameters info) const
{
    std::string buffer(BUFFER_SIZE, '\0');
    defaultRead(queue, info, buffer);

    const char *bufferInChar{buffer.c_str()};
    char newBuffer[BUFFER_SIZE];
    strcpy(newBuffer, bufferInChar);

    ThreadPool::OperateCreator *operateCreator = queue.m_mapCreator.get()->atOperateMap(info.operateToCreate).get();
    operateCreator->addToQueue(queue, {std::make_shared<std::string_view>(newBuffer),
                                       info.version, info.sockfd});
}

uint Read::removeSpacesAndTabs(std::string &str)
{
    // n is length of the original string
    int n = str.length();

    // i points to next position to be filled in
    // output string/ j points to next character
    // in the original string
    int i{0}, j{-1};
    uint numberOfSpaces{0};

    // this flag sets to 'true' if space was found
    bool spaceFound{false};

    // Handles leading spaces
    while (++j < n && (str[j] == ' ' || str[j] == '\t'))
        ;

    // read all characters of original string
    while (j < n)
    {
        // if current characters is non-space
        if (str[j] != ' ' && str[j] != '\t')
        {
            // remove preceding spaces before dot,
            // comma & question mark
            if ((str[j] == ',' || str[j] == '\r' || str[j] == '\n') &&
                i - 1 >= 0 && (str[i - 1] == ' ' || str[i - 1] == '\t'))
            {
                str[i - 1] = str[j++];
            }

            else
            {
                // copy current character at index i
                // and increment both i and j
                str[i++] = str[j++];
            }

            // set space flag to false when any
            // non-space character is found
            spaceFound = false;
        }
        // if current character is a space
        else if (str[j++] == ' ' || str[j++] == '\t')
        {
            // If space is encountered for the first
            // time after a word, put one space in the
            // output and set space flag to true
            if (!spaceFound)
            {
                str[i++] = ' ';
                spaceFound = true;
                ++numberOfSpaces;
            }
        }
    }

    // Remove trailing spaces
    if (i <= 1)
    {
        str.erase(str.begin() + i, str.end());
    }
    else
    {
        str.erase(str.begin() + i, str.end());
    }

    return numberOfSpaces;
}

inline void Read::WriteError(ThreadPool::Queue &queue, const ThreadPool::readParameters info, uint errorCode)
{
    ThreadPool::ErrorWriteCreator errorWriteCreate;
    errorWriteCreate.addToQueue(queue, {std::make_shared<std::string_view>(""), info.version, info.sockfd, errorCode});
}

void Read::defaultRead(ThreadPool::Queue &queue, const ThreadPool::readParameters info, std::string &buffer)
{
    const auto valread = read(info.sockfd, buffer.data(), buffer.size() - 1);

    //Checks if an error happened. If so, it calls to Error Write
    if (valread < 0)
    {
        WriteError(queue, info, 1);
        return;
    }

    //Check if the client's write was for closing
    if (valread == 0)
    {
        close(info.sockfd);
    }

    buffer.resize(valread);

    transform(buffer.begin(), buffer.end(), buffer.begin(), ::toupper);

    bool even{true};
    if (std::any_of(buffer.end() - 4, buffer.end(), [&even](char &c) {
            if (even)
            {
                even = false;
                return c != '\r';
            }
            even = true;
            return c != '\n';
        }))
    {
        WriteError(queue, info, 4);
        return;
    }

    buffer.erase(buffer.end() - 4, buffer.end());
}

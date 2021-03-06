#ifndef PROJ_DIRECTORYSERVER_H
#define PROJ_DIRECTORYSERVER_H

#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include "MessageStructures.h"
#include "Message.h"
#include "Server.h"
#include "Client.h"
#include <new>
#include <memory>
#include <boost/thread.hpp>

#define TIMEOUT 30000
#define INTERVAL 1000
#define DEFAULT_LISTEN_PORT 3000
#define DATABASE_DIR "../database/"
#define THUMBNAILS_DIR "../thumbnails/"
#define DIRECTORY_FILE "directory.txt"
#define USER_FILE "users.txt"

using namespace MessageStructures;
using namespace MessageStructures::Control;
using namespace MessageStructures::User;
using namespace MessageStructures::User::Authentication;

class DirectoryServer : Server, Client {
private:
    struct User {
        std::string username;
        std::string password;
        std::string address;
        std::string token;
        bool authenticated;
        int portNum = DEFAULT_LISTEN_PORT;
        std::vector<std::string> images;
        std::vector<MessageStructures::User::ViewImageRequest> requests;
        std::vector<std::pair<MessageStructures::User::ViewImageRequest, bool>> pendingRequests;
        time_t lastSeen;

        const std::string &getUsername() const;

        void setUsername(const std::string &username);

        const std::string &getPassword() const;

        void setPassword(const std::string &password);

        const std::string &getAddress() const;

        void setAddress(const std::string &address);

        const std::string &getToken() const;

        void setToken(const std::string &token);

        bool isAuthenticated() const;

        void setAuthenticated(bool isAuthenticated);

        int getPortNum() const;

        void setPortNum(int portNum);

        const std::vector<std::string> &getImages() const;

        void setImages(const std::vector<std::string> &images);

        time_t getLastSeen() const;

        void setLastSeen(time_t lastSeen);

        bool imageExists(const std::string &imageName);

        void addImage(const std::string &imageName);

        void delImage(const std::string &imageName);

        void addRequest(MessageStructures::User::ViewImageRequest request);

        void removeRequest(int index);

        void addPendingRequest(MessageStructures::User::ViewImageRequest request, bool accepted);

        void removePendingRequest(int index);

        const std::vector<MessageStructures::User::ViewImageRequest> &getImageRequests() const;

        const std::vector<std::pair<MessageStructures::User::ViewImageRequest, bool>> &getUserPendingRequests() const;

        const std::vector<MessageStructures::User::ViewImageRequest> &getUserRequests() const;

        void setRequests(const std::vector<MessageStructures::User::ViewImageRequest> &requests);
    };

    std::unordered_map<std::string, User> users;
    std::string hostname;
    int port;
    std::string databasePath;
    std::string directoryFile;
    std::string usersFile;
    boost::shared_ptr<DirectoryServer> directoryServer;

public:
    explicit DirectoryServer(const std::string &hostname);

    DirectoryServer(const std::string &hostname, int port, const std::string &databasePath,
                    const std::string &directoryFile, const std::string &usersFile);

    void init();

    static void helloListener(boost::shared_ptr<DirectoryServer> directoryServer);

    void static listen(boost::shared_ptr<DirectoryServer> directoryServer);

    void static databasePersistence(boost::shared_ptr<DirectoryServer> directoryServer);

    void loadDatabase();

    void saveDatabase();

    Ack handleHello(Hello req);

    Ack handleAuthHello(AuthenticatedHello req);

    bool userExists(const std::string &username);

    static std::string generateAuthToken();

    bool authorize(const std::string &username, const std::string &token);

    bool authenticate(const std::string &username, const std::string &hashedPassword);

    static void handleRequest(Message *message, boost::shared_ptr<DirectoryServer> directoryServer);

    SearchReply searchUser(const SearchRequest &req);

    LoginReply loginUser(const LoginRequest &req);

    LogoutReply logoutUser(const LogoutRequest &req);

    ShowOnlineReply showOnline(const ShowOnlineRequest &req);

    FeedReply feed(const FeedRequest &req);

    FeedProfileReply feedProfile(const FeedProfileRequest &req);

    RegisterReply registerUser(const RegisterRequest &req);

    AddImageReply addImage(const AddImageRequest &req);

    DeleteImageReply delImage(const DeleteImageRequest &req);

    ViewImageReply viewImage(const ViewImageRequest &req);

    GetRequestsReply getRequests(const GetRequests &req);

    GetPendingRequestsReply getPendingRequests(const GetPendingRequests &req);

    AddViewerReply acceptRequest(const AddViewerRequest &req);

    DenyViewerReply denyRequest(const DenyViewerRequest &req);

    const boost::shared_ptr<DirectoryServer> &getDirectoryServer() const;

    void setDirectoryServer(const boost::shared_ptr<DirectoryServer> &directoryServer);

    ~DirectoryServer();
};

#endif //PROJ_DIRECTORYSERVER_H

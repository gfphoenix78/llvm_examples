//
// Created by Hao Wu on 7/5/19.
//
#include <iostream>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <unordered_map>
extern "C" {
#include <ev.h>
}
static char sockaddr[128];
struct ev_loop *loop;
struct ClientInfo {
    ev_io io;
    int fd;
    std::string name;
};
std::unordered_map<int, ClientInfo*> data_map;
static int
unix_listen(char *socket_address)
{
    int server_sock, len, rc;
    struct sockaddr_un server_sockaddr;
    memset(&server_sockaddr, 0, sizeof(struct sockaddr_un));

    server_sock = socket(AF_UNIX, SOCK_SEQPACKET, 0);
    if (server_sock == -1){
        perror("unix seqpacket");
        return -1;
    }

    server_sockaddr.sun_family = AF_UNIX;
    snprintf(server_sockaddr.sun_path, sizeof(server_sockaddr.sun_path), "/tmp/plcoordinator.%d.sock", (int)getpid());
    unlink(server_sockaddr.sun_path);
    len = sizeof(server_sockaddr);

    rc = bind(server_sock, (struct sockaddr *) &server_sockaddr, len);
    if (rc == -1){
        goto err_out;
    }

    rc = listen(server_sock, 64);
    if (rc == -1){
        goto err_out;
    }

    strcpy(socket_address, server_sockaddr.sun_path);
    return server_sock;

err_out:
    close(server_sock);
    return -1;
}

static void
unix_socket_read(EV_P_ ev_io *w, int revents)
{
    char buffer[128];
    int rc;
    printf("read packets\n");
    rc = recv(w->fd, buffer, sizeof(buffer), 0);
    if (rc==-1) {
        if (errno==EINTR)
            return;
        perror("recvfrom");
        ev_break(loop, EVBREAK_ALL);
    } else if (rc == 0) {
        // disconnect
        ClientInfo *info = data_map[(w->fd)];
        ev_io_stop(loop, w);
        data_map.erase(w->fd);
        delete info;
    }
    // process message
    printf("message[%d] : '%s'\n", rc, buffer);
}
static void
unix_socket_accept(EV_P_ ev_io *w, int revents)
{
    struct sockaddr_un cli_addr;
    socklen_t len = sizeof(cli_addr);
    int cli_fd;
    cli_fd = accept(w->fd, NULL, NULL);
    printf("cli_fd = %d, address=%s, len=%d\n", cli_fd, cli_addr.sun_path, len);
    if (cli_fd == -1) {
        perror("accept");
        return;
    }
    ClientInfo *info = new ClientInfo;
    info->fd = cli_fd;
    data_map.insert({{cli_fd, info}});
    ev_io_init(&info->io, unix_socket_read, cli_fd, EV_READ);
    ev_io_start(loop, &info->io);
}
static int
unix_dial(const char *socket_address)
{
    struct sockaddr_un remote_addr;
    int fd, rc;
    memset(&remote_addr, 0, sizeof(remote_addr));

    fd = socket(AF_UNIX, SOCK_DGRAM, 0);
    if (fd == -1)
        return -1;
    remote_addr.sun_family = AF_UNIX;
    strncpy(remote_addr.sun_path, socket_address, sizeof(remote_addr.sun_path));

    rc = connect(fd, (const struct sockaddr*)&remote_addr, sizeof(remote_addr));
    if (rc == -1)
        goto err_out;
    return fd;

err_out:
    close(fd);
    return -1;
}
int main()
{
    char buffer[128];
    struct sockaddr_un cli_addr;
    socklen_t len;
    int fd, cli_fd, rc;

    fd = unix_listen(sockaddr);
    printf("fd = %d, sockaddr='%s'\n", fd, sockaddr);
    memset(&sockaddr, 0, sizeof(sockaddr));

    loop = EV_DEFAULT;

    ev_io main_io;
    ev_io_init(&main_io, unix_socket_accept, fd, EV_READ);
    ev_io_start(loop, &main_io);


    ev_run(loop, 0);

//    while (1) {
//        rc = recvfrom(fd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cli_addr, &len);
//        if (rc==-1) {
//            if (errno==EINTR)
//                continue;
//            perror("recvfrom");
//            break;
//        }
//        // process message
//        printf("message[%d] : '%s'\n", rc, buffer);
//        if (rc==0)
//            break;
//    }

    printf("cli_fd = %d", cli_fd);
    close(fd);
    return 0;
}
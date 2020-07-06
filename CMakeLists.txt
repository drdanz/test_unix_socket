cmake_minimum_required(VERSION 3.12)
project(test_unix_socket)

add_executable(stream_server)
target_sources(stream_server PRIVATE stream-server.c
                                     stream-proto.h)

add_executable(stream_client)
target_sources(stream_client PRIVATE stream-client.c
                                     stream-proto.h)

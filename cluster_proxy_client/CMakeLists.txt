CMAKE_MINIMUM_REQUIRED(VERSION 2.6)

PROJECT(ANANAS_CLUSTER)

SUBDIRS(ananas)


SET(QEDIS_CLUSTER 1)
SET(USE_ZOOKEEPER 1)

ADD_DEFINITIONS(-DQEDIS_CLUSTER=${QEDIS_CLUSTER})
ADD_DEFINITIONS(-DUSE_ZOOKEEPER=${USE_ZOOKEEPER})

if(${QEDIS_CLUSTER} EQUAL 1)
    SUBDIRS(cluster_conn)
    SUBDIRS(qedis_proxy)
endif()

# autocollab_agent_INHA
자율협력 비행 과제 인하대학교 충돌 회피 알고리즘

## Overview
- In-house 알고리즘 및 탑재 시험 interface는 Docker container 상에서 동작
- 통신 체계는 ROS2에 기반
- Python 기반 알고리즘의 의존 라이브러리
  - Numpy
  - Scipy
  - MAVSDK

## Contents
- In-house 탑재 알고리즘은 `sources/agent`에 구현
- `sources/gazebo_interface`, `sources/indoor_interface`는 각각 Gazebo 시뮬레이션 및 실내 비행 시험을 위한 interface

## In-house Algorithm

![MACSPOS ](https://github.com/user-attachments/assets/c3cb99dd-f32f-4140-ab0a-3652d4a30cd0)<?xml version="1.0" encoding="UTF-8"?>

- In-house 알고리즘의 통신 interface는 다음 커스텀 메시지 사용

**AgentExternalState**
| Var               | Type       | Descriptions                      |  Units   | 
|-------------------|------------|-----------------------------------|----------|
|id                 |int16       |ID of the agent                    | -        |
|position           |float32[3]  |NED position                       | m        | 
|velocity           |float32[3]  |NED velocity                       | m/s      |
|ongoing            |int16       |Index of the heading waypoint      | -        |
|timestamp          |float32     |Timestamp of the message           | s        |

**AgentInternalState**
| Var               | Type       | Descriptions                      |  Units   | 
|-------------------|------------|-----------------------------------|----------|
|position           |float32[3]  |NED position                       | m        | 
|velocity           |float32[3]  |NED velocity                       | m/s      |

**AgentInternalSetpoint**
| Var               | Type       | Descriptions                                                |  Units   | 
|-------------------|------------|-------------------------------------------------------------|----------|
|control_mode       |int16       |Control mode. ( 0 : position command, 1 : velocity command ) | -        |
|position_setpoint  |float32[3]  |NED position command                                         | m        | 
|velocity_setpoint  |float32[3]  |NED velocity command                                         | m/s      |

## Update plan
- NED 좌표계 데이터 위도, 경도, 고도로 전환
- 코드 경량화
- 경로점 정보 입력 인터페이스 추가

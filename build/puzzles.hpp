#include <iostream>
#include "sdk/interfaces/ISolveObserver.hpp"
#include "sdk/sdk.hpp"

namespace sdk {
namespace data {
static Grid easy = Grid({{kU, kU, k3, k2, kU, kU, kU, kU, kU},
                         {k2, k8, k1, k6, kU, kU, k3, kU, kU},
                         {kU, k6, kU, kU, k1, k3, kU, kU, k8},
                         {kU, kU, k9, k5, kU, k6, kU, k2, kU},
                         {kU, kU, kU, kU, k3, kU, kU, kU, k1},
                         {k5, kU, kU, kU, k2, kU, k4, k6, k3},
                         {k4, k5, kU, k8, kU, k1, k9, kU, kU},
                         {kU, k9, kU, kU, kU, kU, kU, k1, kU},
                         {k3, kU, kU, kU, k9, k7, k6, k8, kU}});

static Grid hard = Grid({{k4, kU, k7, k1, kU, k3, kU, kU, kU},
                         {k9, k1, kU, kU, kU, kU, kU, kU, kU},
                         {k6, kU, kU, kU, kU, k4, kU, k9, kU},
                         {k1, k3, kU, kU, kU, kU, kU, kU, k5},
                         {kU, k9, k8, kU, kU, k2, k7, kU, kU},
                         {k7, kU, kU, kU, k5, k8, k2, kU, kU},
                         {kU, kU, kU, kU, kU, kU, kU, k7, k3},
                         {kU, kU, k9, kU, k7, k6, kU, k5, kU},
                         {kU, kU, kU, k4, kU, k5, kU, kU, kU}});

static Grid expert = Grid({{k7, kU, kU, kU, kU, kU, kU, kU, kU},
                           {k2, k4, k9, kU, kU, kU, kU, k8, kU},
                           {kU, k5, kU, kU, kU, kU, k3, kU, kU},
                           {k3, kU, kU, kU, k5, kU, kU, kU, kU},
                           {kU, kU, kU, kU, k9, k6, kU, kU, kU},
                           {kU, kU, k6, kU, k8, k4, k7, kU, kU},
                           {kU, kU, kU, k6, k7, kU, k5, kU, kU},
                           {kU, kU, kU, kU, kU, kU, kU, k4, k9},
                           {kU, kU, kU, kU, k4, k9, kU, k2, kU}});

static Grid ctc = Grid({{k1, kU, kU, kU, kU, kU, kU, kU, kU},
                        {kU, kU, kU, k6, kU, kU, kU, kU, kU},
                        {kU, k6, kU, k9, k3, k5, kU, kU, kU},
                        {kU, kU, k2, k3, k4, kU, kU, k6, kU},
                        {k3, kU, kU, kU, kU, k1, kU, kU, k2},
                        {kU, kU, kU, kU, kU, kU, kU, k8, k4},
                        {kU, k5, kU, kU, k6, kU, kU, kU, kU},
                        {kU, kU, k1, kU, kU, k2, kU, k9, kU},
                        {k8, kU, kU, kU, kU, kU, kU, k7, k1}});

static Grid ctc2 = Grid({{kU, kU, k1, k2, kU, k3, k4, kU, kU},
                         {kU, kU, kU, k6, kU, k7, kU, kU, kU},
                         {k5, kU, kU, kU, kU, kU, kU, kU, k3},
                         {k3, k7, kU, kU, kU, kU, kU, k8, k1},
                         {kU, kU, kU, kU, kU, kU, kU, kU, kU},
                         {k6, k2, kU, kU, kU, kU, kU, k3, k7},
                         {k1, kU, kU, kU, kU, kU, kU, kU, k8},
                         {kU, kU, kU, k8, kU, k5, kU, kU, kU},
                         {kU, kU, k6, k4, kU, k2, k5, kU, kU}});

static Grid ctc3 = Grid({{kU, kU, kU, kU, k5, kU, k7, kU, k2},
                         {k8, kU, kU, kU, kU, kU, kU, k6, kU},
                         {kU, kU, kU, k1, kU, kU, kU, k5, k4},
                         {kU, kU, kU, kU, k3, kU, kU, kU, kU},
                         {k1, k3, kU, k7, k6, kU, kU, k8, kU},
                         {kU, k6, k4, kU, kU, kU, k1, kU, kU},
                         {k3, k1, k2, kU, k8, kU, kU, kU, kU},
                         {kU, k9, kU, kU, kU, k5, kU, kU, kU},
                         {kU, kU, kU, kU, kU, k3, k9, kU, kU}});

static Grid xwing = Grid({{kU, k3, kU, k4, k8, kU, k6, kU, k9},
                          {kU, kU, kU, kU, k2, k7, kU, kU, kU},
                          {k8, kU, kU, k3, kU, kU, kU, kU, kU},
                          {kU, k1, k9, kU, kU, kU, kU, kU, kU},
                          {k7, k8, kU, kU, kU, k2, kU, k9, k3},
                          {kU, kU, kU, kU, kU, k4, k8, k7, kU},
                          {kU, kU, kU, kU, kU, k5, kU, kU, k6},
                          {kU, kU, kU, k1, k3, kU, kU, kU, kU},
                          {k9, kU, k2, kU, k4, k8, kU, k1, kU}});

static Grid ywing = Grid({{kU, kU, kU, kU, kU, kU, kU, kU, kU},
                          {kU, kU, kU, k1, kU, k7, kU, kU, k8},
                          {kU, k7, kU, k3, k9, k2, k5, k4, k1},
                          {kU, kU, k4, kU, kU, kU, kU, k9, k2},
                          {kU, kU, k5, kU, kU, kU, k6, kU, kU},
                          {k9, k3, kU, kU, kU, kU, k4, kU, kU},
                          {k1, k9, k2, k7, k8, k5, kU, k6, kU},
                          {k5, kU, kU, k4, kU, k3, kU, kU, kU},
                          {kU, kU, kU, kU, kU, kU, kU, kU, kU}});

static Grid swordfish = Grid({{kU, kU, k7, kU, kU, kU, k2, k8, kU},
                              {kU, kU, k4, kU, k2, k5, kU, kU, kU},
                              {k2, k8, kU, kU, kU, k4, k6, kU, kU},
                              {kU, k9, kU, kU, kU, k6, kU, kU, kU},
                              {k3, kU, kU, kU, kU, kU, kU, kU, k2},
                              {kU, kU, kU, k1, kU, kU, kU, k9, kU},
                              {kU, kU, k6, k2, kU, kU, kU, k7, k5},
                              {kU, kU, kU, k5, k7, kU, k4, kU, kU},
                              {kU, k7, k8, kU, kU, kU, k3, kU, kU}});

static Grid min = Grid({{kU, kU, kU, kU, kU, kU, kU, k1, kU},
                        {kU, kU, kU, kU, kU, k2, kU, kU, k3},
                        {kU, kU, kU, k4, kU, kU, kU, kU, kU},
                        {kU, kU, kU, kU, kU, kU, k5, kU, kU},
                        {k4, kU, k1, k6, kU, kU, kU, kU, kU},
                        {kU, kU, k7, k1, kU, kU, kU, kU, kU},
                        {kU, k5, kU, kU, kU, kU, k2, kU, kU},
                        {kU, kU, kU, kU, k8, kU, kU, k4, kU},
                        {kU, k3, kU, k9, k1, kU, kU, kU, kU}});

static Grid diabolical = Grid({{kU, k5, kU, k1, kU, kU, kU, k2, k8},
                               {k4, kU, kU, kU, kU, kU, kU, kU, kU},
                               {kU, kU, kU, k5, kU, k7, k4, kU, k3},
                               {kU, kU, kU, kU, k5, k1, kU, k8, kU},
                               {kU, kU, k1, k8, kU, k9, k6, kU, kU},
                               {kU, k8, kU, k3, k6, kU, kU, kU, kU},
                               {k1, kU, k5, k7, kU, k3, kU, kU, kU},
                               {kU, kU, kU, kU, kU, kU, kU, kU, k7},
                               {k6, k9, kU, kU, kU, k4, kU, k1, kU}});

}  // namespace data
}  // namespace sdk
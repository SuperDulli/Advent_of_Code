file = open("input", "r")
transmission = file.read()  # file cannot contain newline
file.close()


def hex_to_bin(h):
    h_size = len(h) * 4
    return (bin(int(h, 16))[2:]).zfill(h_size)


def parse_packet(p):
    version = int(p[:3], 2)
    p_type = int(p[3:6], 2)
    payload = 0
    p_len = 0
    sub_p_len = -1
    if p_type == 4:  # literal
        group_start = 6
        groups = p[group_start+1:group_start+5]
        while p[group_start] == '1':
            group_start += 5
            groups += p[group_start+1:group_start+5]
        payload = int(groups, 2)
        p_len = group_start + 5
    else:  # operator
        payload = []
        if p[6] == '0':
            sub_p_len = int(p[7:7+15], 2)
            sub_p_len_left = sub_p_len
            sub_p_start = 22  # 7 + 15
            while sub_p_len_left > 0:
                sub_version, sub_type, sub_payload, sub_len, _ = parse_packet(p[sub_p_start:sub_p_start+sub_p_len_left])
                payload.append((sub_version, sub_type, sub_payload, sub_len, sub_p_len))
                sub_p_start += sub_len
                sub_p_len_left -= sub_len
            p_len = 7 + 15 + sub_p_len
        else:  # type ID 1
            num_of_sub_p = int(p[7:7+11], 2)
            sub_p_start = 18  # 7 + 11
            sub_p_len = 0
            while num_of_sub_p > 0:
                sub_version, sub_type, sub_payload, sub_len, _ = parse_packet(p[sub_p_start:])
                payload.append((sub_version, sub_type, sub_payload, sub_len, sub_p_len))
                sub_p_len += sub_len
                sub_p_start += sub_len
                num_of_sub_p -= 1
            p_len = 7 + 11 + sub_p_len

    return version, p_type, payload, p_len, sub_p_len


def sum_version(p):
    s = 0
    s += p[0]
    if isinstance(p[2], list):
        for sub_p in p[2]:
            s += sum_version(sub_p)
    return s


print("Examples:")
let1 = parse_packet("110100101111111000101000")
op1 = parse_packet("00111000000000000110111101000101001010010001001000000000")
op2 = parse_packet(hex_to_bin("8A004A801A8002F478"))
op3 = parse_packet(hex_to_bin("620080001611562C8802118E34"))
op4 = parse_packet(hex_to_bin("C0015000016115A2E0802F182340"))
op5 = parse_packet(hex_to_bin("A0016C880162017C3686B18A3D4780"))
print(sum_version(let1), sum_version(op1), sum_version(op2), sum_version(op3), sum_version(op4), sum_version(op5))

packet = hex_to_bin(transmission)
parsed_packet = parse_packet(packet)
print("Answer for part one: ", sum_version(parsed_packet))

# Part 2
import math


def evaluate_packet(p):
    version, p_type, payload, p_len, sub_p_len = p
    if p_type == 0:  # sum
        if isinstance(payload, list):
            return sum([evaluate_packet(sub_p) for sub_p in payload])
        else:
            return evaluate_packet(payload)
    elif p_type == 1:  # product
        if isinstance(payload, list):
            return math.prod([evaluate_packet(sub_p) for sub_p in payload])
        else:
            return evaluate_packet(payload)
    elif p_type == 2:  # minimum
        if isinstance(payload, list):
            return min([evaluate_packet(sub_p) for sub_p in payload])
        else:
            return evaluate_packet(payload)
    elif p_type == 3:  # maximum
        if isinstance(payload, list):
            return max([evaluate_packet(sub_p) for sub_p in payload])
        else:
            return evaluate_packet(payload)
    elif p_type == 4:  # literal
        return payload
    elif p_type == 5:  # greater than
        if evaluate_packet(payload[0]) > evaluate_packet(payload[1]):
            return 1
        else:
            return 0
    elif p_type == 6:  # less than
        if evaluate_packet(payload[0]) < evaluate_packet(payload[1]):
            return 1
        else:
            return 0
    elif p_type == 7:  # equal to
        if evaluate_packet(payload[0]) == evaluate_packet(payload[1]):
            return 1
        else:
            return 0


print("Examples:")
sum1 = parse_packet(hex_to_bin("C200B40A82"))
prod1 = parse_packet(hex_to_bin("04005AC33890"))
min1 = parse_packet(hex_to_bin("880086C3E88112"))
max1 = parse_packet(hex_to_bin("CE00C43D881120"))
less1 = parse_packet(hex_to_bin("D8005AC2A8F0"))
great1 = parse_packet(hex_to_bin("F600BC2D8F"))
equal1 = parse_packet(hex_to_bin("9C005AC2F8F0"))
equal2 = parse_packet(hex_to_bin("9C0141080250320F1802104A08"))
exampels = [sum1, prod1, min1, max1, less1, great1, equal1, equal2]
print(list(evaluate_packet(x) for x in exampels))

print("Answer for part two: ", evaluate_packet(parsed_packet))